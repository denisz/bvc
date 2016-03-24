//
//  UIWindow.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "UIWindow.hpp"

USING_NS_CC;
using namespace UIKit;

UIWindow::UIWindow()
: _scene(nullptr)
, _rootViewController(nullptr) {

}

UIWindow::~UIWindow() {
    CC_SAFE_RELEASE_NULL(_scene);
    CC_SAFE_RELEASE_NULL(_rootViewController);
}

bool UIWindow::init() {
    _scene = Scene::create();
    CC_SAFE_RETAIN(_scene);
    return UIViewController::init();
}

void UIWindow::viewDidLoad() {
    _scene->addChild(this->view());
}

void UIWindow::setRootViewController(UIViewController* controller) {
    if (controller != nullptr) {
        if (_rootViewController != nullptr) {
            _rootViewController->removeFromParent();
            CC_SAFE_RELEASE_NULL(_rootViewController);
        }
        _rootViewController = controller;
        showViewController(controller);
    }
}

cocos2d::Scene* UIWindow::scene() {
    return _scene;
};