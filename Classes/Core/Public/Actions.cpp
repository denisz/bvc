//
//  Actions.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#include "Actions.hpp"

using namespace common;

Actions::Actions()
: delegate(nullptr) {
    
}

Actions::~Actions() {
    unsubscribe();
    delegate = nullptr;
}

Actions* Actions::createWithDelegate(Delegate* delegate) {
    auto ref = new Actions();
    
    if (ref->init()) {
        ref->delegate = delegate;
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

Actions* Actions::create() {
    auto ref = new Actions();
    
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool Actions::init() {
    return true;
}

void Actions::subscribe() {
    NotificationCenter::subscribe<internal::ActionsClient::Events>(this);
    if (delegate != nullptr) {
        delegate->didSubscribeAction();
    }
}

void Actions::unsubscribe() {
    NotificationCenter::unsubscribe<internal::ActionsClient::Events>(this);
    if (delegate != nullptr) {
        delegate->didUnsubscribeAction();
    }
}

void Actions::onCall(internal::ActionsClient::Event* event) {
    if (delegate != nullptr) {
        delegate->processAction(event);
    }
}

void Actions::pause() {
    unsubscribe();
}

void Actions::resume() {
    subscribe();
}

void Actions::stop() {
   unsubscribe(); 
}