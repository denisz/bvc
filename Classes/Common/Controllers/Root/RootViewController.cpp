//
//  RootViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/1/16.
//
//

#include "RootViewController.hpp"

using namespace game;

RootViewController* RootViewController::_instance;

RootViewController* RootViewController::sharedInstance() {
    if (RootViewController::_instance == nullptr) {
        RootViewController::_instance = RootViewController::create();
        CC_SAFE_RETAIN(RootViewController::_instance);
    }
    
    return RootViewController::_instance;
}

RootViewController::RootViewController()
: _navigationController(nullptr) {
    _autoSubscribeAction = false;
    _autoSubscribeReaction = false;
}

RootViewController::~RootViewController() {
    CC_SAFE_RELEASE_NULL(_navigationController);
}

void RootViewController::viewDidLoad() {
    _navigationController = UIKit::UINavigationController::create();
    showViewController(_navigationController);
}

void RootViewController::pushViewController(UIKit::UIViewController* viewController, bool animated) {
    if (_navigationController != nullptr) {
        _navigationController->pushViewController(viewController, animated);
    }
}

void RootViewController::popViewControllerAnimated(bool animated) {
    if (_navigationController != nullptr) {
        _navigationController->popViewControllerAnimated(animated);
    }
}
