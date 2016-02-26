//
//  BaseUIViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "BaseUIViewController.hpp"


using namespace game;

bool BaseUIViewController::init() {
    auto transition = TransitionManager::create();
    CC_SAFE_AUTORELEASE(transition);
    this->setTransition(transition);
    return UIViewController::init();
}