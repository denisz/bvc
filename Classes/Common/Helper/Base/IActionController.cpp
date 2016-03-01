//
//  IActionController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#include "IActionController.hpp"

using namespace game;

IActionController::IActionController()
: _actions(nullptr)
, _actionsRouter(nullptr)
, _autoSubscribeAction(true) {
    
}

IActionController::~IActionController() {
    CC_SAFE_RELEASE_NULL(_actions);
    CC_SAFE_RELEASE_NULL(_actionsRouter);
}

bool IActionController::init() {
    _actions = common::Actions::createWithDelegate(this);
    _actionsRouter = common::ActionsRouter::create();
    
    if (_autoSubscribeAction) {
        subscribe();
    }
    
    return true;
}

void IActionController::subscribe() {
    _actions->subscribe();
}

void IActionController::unsubscribe() {
    _actions->unsubscribe();
}

void IActionController::processAction(internal::ActionsClient::Event* event) {
    _actionsRouter->process(event);
}

common::ActionsRouter* IActionController::actions() {
    return _actionsRouter;
}