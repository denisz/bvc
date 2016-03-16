//
//  CurrentUserController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "CurrentUserController.hpp"

using namespace game;
using namespace common;


bool CurrentUserController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* CurrentUserController::logInAsync(const std::string &login, const std::string &password) {
    auto cmd = RequestCommand::createWithCommand("account/auth");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->cachePolicy = kCachePolicyNetworkElseCache;
    cmd->setValue("/email",     login);
    cmd->setValue("/password",  password);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::signUpAsync(const std::string &login, const std::string &password) {
    auto cmd = RequestCommand::createWithCommand("account/signup");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/email",     login);
    cmd->setValue("/password",  password);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::logOutAsync() {
    auto cmd = RequestCommand::createWithCommand("account/logout");
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::requestPasswordResetAsync() {
    auto cmd = RequestCommand::createWithCommand("account/password");
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::removeFriend(const std::string &profileId) {
    auto cmd = RequestCommand::createWithCommand("account/removeFriend");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/id", profileId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::addFriend(const std::string &profileId) {
    auto cmd = RequestCommand::createWithCommand("account/addFriend");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/id", profileId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::removeFromBlacklist(const std::string &profileId) {
    auto cmd = RequestCommand::createWithCommand("account/removeFromBlacklist");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/id", profileId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::addToBlacklist(const std::string &profileId) {
    auto cmd = RequestCommand::createWithCommand("account/addToBlacklist");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/id", profileId);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::friends() {
    auto cmd = RequestCommand::createWithCommand("account/friends");
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* CurrentUserController::blacklist() {
    auto cmd = RequestCommand::createWithCommand("account/blacklist");
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    return runCommandInBackground(*cmd);
}

