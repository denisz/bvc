//
//  Router.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "Router.hpp"

using namespace common;
using namespace internal::network;

Router::Router()
: _enabled(true)
, delegate(nullptr) {
}

Router::~Router(){
    this->_handlers.clear();
    
    delegate = nullptr;
}

bool Router::init() {
    this->_handlers = std::map<std::string, HandlerList>();
    return true;
}

Router* Router::create() {
    auto router = new Router();
    if (router->init()) {
        return router;
    }
    
    CC_SAFE_DELETE(router);
    return nullptr;
}

Router* Router::command(const std::string& path, const Handler& handler) {
    if (this->_handlers.find(path) != this->_handlers.end()) {
        auto tmp = this->_handlers[path];
        tmp.push_back(handler);
    } else {
        auto handlerList = HandlerList();
        handlerList.push_back(handler);
        this->_handlers.emplace(path, handlerList);
    }
    
    return this;
}

Router* Router::command(const std::string& path, std::initializer_list<Handler> handlers) {
    if (this->_handlers.find(path) != this->_handlers.end()) {
        auto tmp = this->_handlers[path];
        tmp.insert( tmp.end(), handlers.begin(), handlers.end() );
        this->_handlers[path] = tmp;
    } else {
        auto handlerList = HandlerList();
        handlerList.insert(handlerList.end(), handlers.begin(), handlers.end());
        this->_handlers.emplace(path, handlerList);
    }
    
    return this;
}

Router* Router::use(Handlers& handlers) {
    for (auto &elem: handlers) {
        _handlers[elem.first] = elem.second;
    }
    return this;
}

void Router::process(Response& res) {
    if (_enabled) {
        this->worker(this->_handlers, PATH_GLOBAL, res);
        this->worker(this->_handlers, res.command(), res);
    }
}

void Router::error(Response& res) {
    if (_enabled) {
        this->worker(this->_handlers, PATH_GLOBAL, res);
        this->worker(this->_handlers, res.command(), res);
    }
}

void Router::exception(Response& res, Error& error) {
    auto handlers = this->_handlers;
    auto it = handlers.find(PATH_ERROR);
    if (it != handlers.end()) {
        auto handlers = it->second;
        for (auto &worker: handlers) {
            worker(&res);
        }
    }
}

void Router::worker(std::map<std::string, HandlerList>& handlers, const std::string& command, Response& res) {

    auto it = handlers.find(command);
    if (it != handlers.end()) {
        auto handlers = it->second;
        try {
            for (auto &worker: handlers) {
                if (!worker(&res)) {
                    break;
                }
            }
        } catch(Error& err) {
            exception(res, err);
        }
    }
}

void Router::setEnabled(bool value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _enabled = value;
}

void Router::pause() {
    setEnabled(false);
}

void Router::resume() {
    setEnabled(true);
}

void Router::stop() {
    setEnabled(false);
}
