//
//  PvPController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#include "PvPController.hpp"

using namespace game;
bool PvPController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* PvPController::initWithBot(const std::string& botId) {
    auto cmd = RequestCommand::createWithCommand("pvp/withBot");
    cmd->setValue("/botId", botId);
    CC_SAFE_AUTORELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::createChallenge(const internal::BVValueMap& options) {
    auto cmd = RequestCommand::createWithCommand("pvp/create");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue(options);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::createDefaultChallenge() {
    internal::BVValueMap options;
    
    options["ratingOn"]         = false;
    options["starters"]         = false;
    options["goldCrystals"]     = 24;
    options["silverCrystals"]   = 22;
    options["turnTime"]         = 60;
    options["deckTime"]         = 300;
    
    return createChallenge(options);
}

CommandRunner::Handler* PvPController::acceptDuel() {
    auto cmd = RequestCommand::createWithCommand("pvp/approve");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/approve", true);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::denyDuel() {
    auto cmd = RequestCommand::createWithCommand("pvp/approve");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/approve", false);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::join(const std::string& gameId) {
    auto cmd = RequestCommand::createWithCommand("pvp/join");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/gameId", gameId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::cancel() {
    auto cmd = RequestCommand::createWithCommand("pvp/cancel");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::cancelRandom() {
    auto cmd = RequestCommand::createWithCommand("pvp/cancel");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::hasCreated() {
    auto cmd = RequestCommand::createWithCommand("pvp/hasCreated");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::hasRandom() {
    auto cmd = RequestCommand::createWithCommand("pvp/hasRandom");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* PvPController::random() {
    auto cmd = RequestCommand::createWithCommand("pvp/random");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/any", true);
    
    return runCommandInBackground(*cmd);
}
