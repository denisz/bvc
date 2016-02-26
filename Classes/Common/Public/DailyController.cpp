//
//  DailyController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#include "DailyController.hpp"

using namespace game;
bool DailyController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* DailyController::getAsync() {
    auto cmd = RequestCommand::createWithCommand("dailyq/list");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);

}