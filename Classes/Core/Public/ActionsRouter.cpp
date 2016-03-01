//
//  ActionsRouter.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#include "ActionsRouter.hpp"

using namespace common;

ActionsRouter::ActionsRouter(){
}

ActionsRouter::~ActionsRouter(){
    this->_handlers.clear();
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
    
    for (auto worker: _handlers) {
        if (worker.path == command || worker.path == PATH_GLOBAL_ACTION) {
            worker.handler(event);
        }
    }
    CC_SAFE_RELEASE(event);
}