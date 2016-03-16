//
//  ChatController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#include "ChatController.hpp"

using namespace game;
bool ChatController::init() {
    return ICommandController::init();
}

CommandRunner::Handler* ChatController::sendMessageAsync(CHANNELS channel, const std::string& message) {
    auto cmd = RequestCommand::createWithCommand("chat/send");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/type", toString(channel));
    cmd->setValue("/msg",  message);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* ChatController::sendMessageAsync(CHANNELS channel, const std::string& to,const std::string& message) {
    auto cmd = RequestCommand::createWithCommand("chat/send");
    CC_SAFE_DEFRREDRELEASE(cmd);
    cmd->setValue("/type",  toString(channel));
    cmd->setValue("/msg",   message);
    cmd->setValue("/to",    to);
    
    return runCommandInBackground(*cmd);
}

CommandRunner::Handler* ChatController::sendPublicMessageAsync(const std::string& message) {
    return sendMessageAsync(CHANNELS::PUBLIC, message);
}

CommandRunner::Handler* ChatController::sendP2PMessageAsync(const std::string& to, const std::string& message) {
    return sendMessageAsync(CHANNELS::PRIVATE, to, message);
}


