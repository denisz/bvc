//
//  DeckController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#include "DeckController.hpp"

using namespace game;
bool DeckController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* DeckController::create(const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("deck/save");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue(data);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::copy(const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("deck/save");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue(data);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::save(const internal::BVValueMap& data) {
    auto cmd = RequestCommand::createWithCommand("deck/save");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue(data);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::remove(const std::string& deckId) {
    auto cmd = RequestCommand::createWithCommand("deck/delete");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/id", deckId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::list() {
    auto cmd = RequestCommand::createWithCommand("deck/list");
    CC_SAFE_AUTORELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::rename(const std::string& deckId, const std::string& name) {
    auto cmd = RequestCommand::createWithCommand("deck/rename");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/id", deckId);
    cmd->setValue("/name", name);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::changeCover(const std::string& deckId, const std::string& cover) {
    auto cmd = RequestCommand::createWithCommand("deck/changeCover");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/deckId", deckId);
    cmd->setValue("/cover", cover);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::addBookmark(const std::string& deckId) {
    auto cmd = RequestCommand::createWithCommand("deck/addBookmark");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/deckId", deckId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* DeckController::removeBookmark(const std::string& deckId) {
    auto cmd = RequestCommand::createWithCommand("deck/removeBookmark");
    CC_SAFE_AUTORELEASE(cmd);
    cmd->setValue("/deckId", deckId);
    
    return runCommandInBackground(*cmd);
}
