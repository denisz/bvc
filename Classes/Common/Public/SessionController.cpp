//
//  SessionController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "SessionController.hpp"

using namespace game;
bool SessionController::init() {
    return ICommandController::init();
}

bool SessionController::isAuthenticated() {
    return true;
}

CommandRunner::Handler* SessionController::checkSessionTokenAsync() {
    auto cmd = RequestCommand::createWithCommand("account/checkAuth");
    CC_SAFE_AUTORELEASE(cmd);
    return runCommandInBackground(*cmd);
}