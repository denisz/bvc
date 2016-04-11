//
//  Instruction.cpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#include "Instruction.hpp"


using namespace  Instructions;

Instruction::Instruction()
: _promise(nullptr)
, _finishTask(nullptr) {
    
}

Instruction::~Instruction() {
    CC_SAFE_RELEASE_NULL(_promise);
}

bool Instruction::init() {
    _promise = Promise::taskCompletionSource();
    _finishTask = _promise->task();
    return true;
}

void Instruction::end() {
    CC_SAFE_RELEASE_NULL(_promise);
    std::cout << "Instruction end" << std::endl;
}

void Instruction::begin() {
    serve();
}

void Instruction::complete() {
    _promise->trySetResult(*this);
}

void Instruction::serve() {
    complete();
}

bool Instruction::willServe() {
    return true;
};

Instruction* Instruction::continueWithBlock(const Instruction::TaskHandler &block) {
    _finishTask = _finishTask->continueWithBlock(block);
    return this;
}

Instruction::Task* Instruction::getFinishTask() {
    return _finishTask;
}
