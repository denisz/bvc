//
//  FightController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/21/16.
//
//

#include "FightController.hpp"

using namespace game;

bool FightController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* FightController::pass(int gameId) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "pass");
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::chooseDeck(int gameId, const int deckId) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "choosedeck");
    cmd->setValue("/deckId", deckId);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::deal(int gameId) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "deal");
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::selection(int gameId, const BVValueVector& selection) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "selection");
    cmd->setValue("/cards", selection);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::ability(int gameId, const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "ability");
    cmd->setValue(data);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::dialog(int gameId, const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "dialog");
    cmd->setValue(data);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::surrender(int gameId) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "surrender");
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::equipment(int gameId, const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "equipment");
    cmd->setValue(data);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::draw(int gameId) {
    auto cmd = RequestCommand::createWithCommand("game/act");
    cmd->setValue("/gameid", gameId);
    cmd->setValue("/act", "draw");
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* FightController::saveReplay(int gameId) {
    auto cmd = RequestCommand::createWithCommand("game/saveReplay");
    cmd->setValue("/gameid", gameId);
    CC_SAFE_DEFRREDRELEASE(cmd);
    return runCommandInBackground(*cmd);
}
