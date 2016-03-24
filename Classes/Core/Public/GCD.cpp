//
//  GCD.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/14/16.
//
//

#include "GCD.hpp"

using namespace internal;

GCD::GCD(){
    _UIWsMessageQueue = new std::list<Message>();
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

GCD& GCD::sharedInstance() {
    static GCD instance;
    return instance;
}

void GCD::sendMessageToUIThread(Message msg) {
    sharedInstance()._sendMessageToUIThread(msg);
}

void GCD::_sendMessageToUIThread(Message msg)
{
    std::lock_guard<std::mutex> lk(_UIWsMessageQueueMutex);
    _UIWsMessageQueue->push_back(msg);
}

void GCD::update(float dt)
{
    if (0 == _UIWsMessageQueue->size())
        return;
    
    _UIWsMessageQueueMutex.lock();
    
    if (0 == _UIWsMessageQueue->size())
    {
        _UIWsMessageQueueMutex.unlock();
        return;
    }
    
    std::list<Message> messages;
    while (!_UIWsMessageQueue->empty()) {
        messages.push_back(_UIWsMessageQueue->front());
        _UIWsMessageQueue->pop_front();
    }
    
    _UIWsMessageQueueMutex.unlock();
    
    for (auto &msg : messages) {
        msg();
    }
}
