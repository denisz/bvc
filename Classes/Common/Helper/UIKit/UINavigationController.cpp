//
//  UINavigationController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "UINavigationController.hpp"

using namespace game;

UINavigationController::UINavigationController()
: delegate(nullptr)
, topViewController(nullptr)
, visibleViewController(nullptr) {

}

UINavigationController::~UINavigationController() {
    delegate = nullptr;
    _stackControllers.clear();
}

bool UINavigationController::init() {
    _stackControllers = std::vector<UIViewController*>();
    return UIViewController::init();
}

bool UINavigationController::initWithRootViewContorller(UIViewController* viewController) {
    auto result = UINavigationController::init();
    showViewController(viewController);
    return result;
}

UINavigationController* UINavigationController::create() {
    auto ref = new UINavigationController();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

UINavigationController* UINavigationController::createWithRootViewController(UIViewController* viewController) {
    auto ref = new UINavigationController();
    if (ref->initWithRootViewContorller(viewController)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}


std::vector<UIViewController*> UINavigationController::viewControllers() {
    return _stackControllers;
}

void UINavigationController::showViewController(UIViewController* viewController) {
    
}

void UINavigationController::pushViewController(UIViewController* viewController, bool animated) {
    //поменять транзитион
    
}

UIViewController* UINavigationController::popViewControllerAnimated(bool animated) {
    return nullptr;
}

std::vector<UIViewController*> UINavigationController::popToRootViewControllerAnimated(bool animated) {
    auto stack = std::vector<UIViewController*>();
    
    return stack;
}

std::vector<UIViewController*> UINavigationController::popToViewController(UIViewController* viewController, bool animated) {
    auto stack = std::vector<UIViewController*>();
    
    return stack;
}
