//
//  UserController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "UserController.hpp"

using namespace game;
using namespace common;

bool UserController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* UserController::getAsync(const std::string& profileId, bool extended) {
    auto cmd = RequestCommand::createWithCommand("account/profile");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/id", profileId);
    cmd->setValue("/extended", extended);
    return runCommandInBackground(*cmd);
}
