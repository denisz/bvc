//
//  ICommandController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "ICommandController.hpp"

using namespace game;

ICommandController::ICommandController()
: _commandRunner(nullptr) {
}

ICommandController::~ICommandController() {
    CC_SAFE_RELEASE_NULL(_commandRunner);
}

bool ICommandController::init() {
    auto commandRunner = common::CommandRunner::create();
    CC_SAFE_DEFRREDRELEASE(commandRunner);
    return initWithCommandRunner(commandRunner);
}

bool ICommandController::initWithCommandRunner(common::CommandRunner* commandRunner) {
    _commandRunner = commandRunner;
    _commandRunner->delegate = this;
    CC_SAFE_RETAIN(_commandRunner);
    return true;
}

CommandRunner::Handler* ICommandController::runCommandInBackground(common::RequestCommand &command) {
    return _commandRunner->runCommandAsync(command);
}

void ICommandController::runCommand(common::RequestCommand &command) {
    return _commandRunner->runCommand(command);
}

common::CommandRunner* ICommandController::commandRunner() {
    return _commandRunner;
}

void ICommandController::processResponse(CommandRunner* runner, Response* response) {
    
}



