//
//  RootController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/1/16.
//
//

#include "RootController.hpp"


using namespace game;
RootController* RootController::_instance;

RootController* RootController::getInstance() {
    if (RootController::_instance == nullptr) {
        RootController::_instance = RootController::create();
    }
    
    return RootController::_instance;
}

RootController::RootController(){
    _autoSubscribeAction = false;
    _autoSubscribeReaction = false;
}

bool RootController::init() {
    return GameController::init();
}

void RootController::loadViewController() {
    setView(RootViewController::create());
}

void RootController::setTop(GameController* controller, bool animated) {
    auto view = dynamic_cast<UIKit::UINavigationController*>(getViewController());
    view->setTopViewControllerAnimated(controller->getViewController(), animated);
}

void RootController::push_front(GameController* controller, bool animated) {
    auto view = dynamic_cast<UIKit::UINavigationController*>(getViewController());
    view->pushViewController(controller->getViewController(), animated);
}

void RootController::pop_front(bool animated) {
    auto view = dynamic_cast<UIKit::UINavigationController*>(getViewController());
    view->popViewControllerAnimated(animated);
}

