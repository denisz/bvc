//
//  BotsController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#include "BotsController.hpp"

#include "PvPController.hpp"

using namespace game;
bool BotsController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* BotsController::getAsync() {
    auto cmd = RequestCommand::createWithCommand("account/listBots");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->fromLocalDatastore();
    
    return runCommandInBackground(*cmd);
}

