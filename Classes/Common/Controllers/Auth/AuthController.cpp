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
    _router->command("/command/auth",
                     BV_CALLBACK_1(AuthController::commandAuth, this) );
    
    actionAuth();
    return true;
}

void AuthController::commandAuth(internal::network::Response* res) {
    
}

void AuthController::actionAuth() {
    
}

void AuthController::processOpen() {
    std::cout << "Open websocket" << std::endl;
    NetworkController::processOpen();
}