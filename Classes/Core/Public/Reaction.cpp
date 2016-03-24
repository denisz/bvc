//
//  Reaction.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "Reaction.hpp"
#include "ServiceLocator.hpp"

using namespace common;
using namespace internal::network;
using namespace Bolts;

Reaction* Reaction::createWithDelegate(Delegate* delegate) {
    Reaction* react = new Reaction();
    
    if (react->init()) {
        react->delegate = delegate;
        return react;
    }
    
    CC_SAFE_DELETE(react);
    return nullptr;
}

Reaction* Reaction::create() {
    Reaction* react = new Reaction();
    
    if (react->init()) {
        return react;
    }
    
    CC_SAFE_DELETE(react);
    return nullptr;
}


Reaction::Reaction()
: delegate(nullptr)
, _threadPool(nullptr) {

}

Reaction::~Reaction() {
    unsubscribe();
    CC_SAFE_RELEASE_NULL(_threadPool);
    delegate = nullptr;
}

bool Reaction::init() {
    return true;
}

void Reaction::subscribe() {
    if (_threadPool == nullptr) {
        _threadPool = BFExecutor::defaultExecutor()->createPool(1);
    }
    
    NotificationCenter::subscribe<NetworkClient::Events>(this);
    
    if (delegate != nullptr) {
        delegate->didSubscribe();
    }
}

void Reaction::unsubscribe() {
    NotificationCenter::unsubscribe<NetworkClient::Events>(this);
    if (delegate != nullptr) {
        delegate->didUnsubscribe();
    }
}

void Reaction::onError(Response *res) {
    if (_threadPool != nullptr) {
        CC_SAFE_RETAIN(res);
        _threadPool->addTask(BV_CALLBACK_1(Reaction::handlerErrorMessage, this), res);
    }
}

void Reaction::onReceivedMessage(Response *res) {
    if (_threadPool != nullptr) {
        CC_SAFE_RETAIN(res);
        if (_flagMultiThread) {
            _threadPool->addTask(BV_CALLBACK_1(Reaction::handlerReceivedMessage, this), res);
        } else {
            handlerReceivedMessage(res);
        }
    }
}

void Reaction::handlerErrorMessage(Response *res) {
    if (delegate != nullptr) {
        delegate->processError(*res);
    }
    CC_SAFE_RELEASE(res);
}

void Reaction::handlerReceivedMessage(Response *res) {
    if (delegate != nullptr) {
        delegate->processMessage(*res);
    }
    CC_SAFE_RELEASE(res);
}

void Reaction::onOpen() {
    if (delegate != nullptr) {
        delegate->processOpen();
    }
}

void Reaction::onClose() {
    if (delegate != nullptr) {
        delegate->processClose();
    }
}

void Reaction::pause() {
    if (_threadPool != nullptr) {
        _threadPool->pause();
    }
}

void Reaction::resume() {
    if (_threadPool != nullptr) {
        _threadPool->unpause();
    }
}

void Reaction::stop() {
    if (_threadPool != nullptr) {
        _threadPool->stop();
    }
}

void Reaction::setMode(bool multiThread) {
    _flagMultiThread = multiThread;
}