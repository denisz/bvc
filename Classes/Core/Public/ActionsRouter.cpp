//
//  ActionsRouter.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#include "ActionsRouter.hpp"

using namespace common;

ActionsRouter::ActionsRouter()
: _enabled(true)
, delegate(nullptr) {
}

ActionsRouter::~ActionsRouter(){
    this->_handlers.clear();
    delegate = nullptr;
}

bool ActionsRouter::init() {
    this->_handlers = std::forward_list<HandlerData>();
    return true;
}

ActionsRouter* ActionsRouter::create() {
    auto ref = new ActionsRouter();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

ActionsRouter* ActionsRouter::action(const std::string& path, const Handler& handler) {
    auto h = HandlerData();
    h.path = path;
    h.handler = handler;
    this->_handlers.push_front(h);
    return this;
}

void ActionsRouter::process(internal::ActionsClient::Event* event) {
    auto command = event->command();
    CC_SAFE_RETAIN(event);
    
    for (auto &worker: _handlers) {
        if (worker.path == command || worker.path == PATH_GLOBAL_ACTION) {
            worker.handler(event);
        }
    }
    CC_SAFE_RELEASE(event);
}

void ActionsRouter::setEnabled(bool value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _enabled = value;
}

void ActionsRouter::pause() {
    setEnabled(false);
}

void ActionsRouter::resume() {
    setEnabled(true);
}

void ActionsRouter::stop() {
    setEnabled(false);
}
