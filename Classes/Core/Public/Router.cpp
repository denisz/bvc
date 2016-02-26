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

Router::Router(){
}

Router::~Router(){
    this->_handlers.clear();
    this->_after_handlers.clear();
    this->_before_handlers.clear();
}

bool Router::init() {
    this->_handlers = std::vector<Handler>();
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

void Router::command(const std::string& path, const routerHandler& handler) {
    auto h = Handler();
    h.path = path;
    h.handler = handler;
    this->_handlers.push_back(h);
}

void Router::after(const std::string& path, const routerHandler& handler) {
    auto h = Handler();
    h.path = path;
    h.handler = handler;
    this->_after_handlers.push_back(h);
}

void Router::before(const std::string& path, const routerHandler& handler) {
    auto h = Handler();
    h.path = path;
    h.handler = handler;
    this->_before_handlers.push_back(h);
}

void Router::process(Response& res) {
    this->worker(this->_after_handlers, res);
    this->worker(this->_handlers, res);
    this->worker(this->_before_handlers, res);
}

void Router::error(Response& res) {
    this->worker(this->_after_handlers, res);
    this->worker(this->_handlers, res);
    this->worker(this->_before_handlers, res);
}

void Router::worker(std::vector<Handler>& handlers, internal::network::Response& res) {
    auto command = res.command();
    for (auto worker: handlers) {
        if (worker.path == command || worker.path == PATH_GLOBAL) {
            worker.handler(&res);
        }
    }
}