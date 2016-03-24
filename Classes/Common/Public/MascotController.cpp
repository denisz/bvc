//
//  MascotController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/24/16.
//
//

#include "MascotController.hpp"

using namespace game;

bool MascotController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* MascotController::getAsync() {
    auto cmd = RequestCommand::createWithCommand("mascot/list");
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* MascotController::exchange(const std::string& mascotId) {
    auto cmd = RequestCommand::createWithCommand("mascot/exchange");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/id", mascotId);
    
    return runCommandInBackground(*cmd);

}
