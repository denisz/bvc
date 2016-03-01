//
//  ActionsClient.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#include "ActionsClient.hpp"

using namespace internal;

void ActionsClient::call(Event *event) {
    NotificationCenter::notify(&ActionsClient::Events::onCall, event);
}

bool ActionsClient::init() {
    return true;
}

ActionsClient::Event* ActionsClient::createEventWithCommand(const std::string& cmd) {
    return ActionsClient::Event::createWithCommand(cmd);
}

ActionsClient* ActionsClient::create() {
    auto ref = new ActionsClient();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}