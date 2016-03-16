//
//  AuthController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "AuthController.hpp"

using namespace game;

bool AuthController::init() {
    actionAuth();
    return true;
}

void AuthController::actionAuth() {
    
}

void AuthController::processOpen() {
    std::cout << "Open websocket" << std::endl;
    NetworkController::processOpen();
}

UIKit::UIViewController* AuthController::loadViewController() {
    return AuthViewController::create();
}