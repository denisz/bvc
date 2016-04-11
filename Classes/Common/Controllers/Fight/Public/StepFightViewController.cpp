//
//  StepFightViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/25/16.
//
//

#include "StepFightViewController.hpp"


using namespace game;


StepFightViewController::StepFightViewController()
: _contextFight(nullptr) {}

StepFightViewController::~StepFightViewController() {
    unsubscribeContext();
    CC_SAFE_RELEASE_NULL(_contextFight);
}

bool StepFightViewController::initWithContextFight(ContextFight *contextFight) {
    if (init()) {
        _contextFight = contextFight;
        CC_SAFE_RETAIN(_contextFight);
        subscribeContext();
        return true;
    }
    
    return false;
}

ContextFight* StepFightViewController::context() {
    return _contextFight;
}

void StepFightViewController::subscribeContext() {
    _contextFight->listen(this);
}

void StepFightViewController::unsubscribeContext() {
    _contextFight->stopListening(this);
}
