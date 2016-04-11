//
//  InstructionsPool.cpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#include "InstructionsPool.hpp"

using namespace  Instructions;

InstructionsPool::InstructionsPool()
: _current(nullptr)
, delegate(nullptr)
, _dirty(false)
, _state(State::Wait) {
    _queue = new std::priority_queue<Node>();
}

InstructionsPool::~InstructionsPool() {
    while(!_queue->empty()) {
        auto item = _queue->top().begin()->second;
        CC_SAFE_RELEASE(item);
        _queue->pop();
    }
    CC_SAFE_DELETE(_queue);
}

bool InstructionsPool::init() {
    return true;
}

InstructionsPool* InstructionsPool::create() {
    auto ref = new InstructionsPool();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

void InstructionsPool::addInstruction(int priority, Instruction* instruction) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue->push(createNode(priority, instruction));
    
    if (_dirty == false) {
        if (delegate != nullptr)
            delegate->didWaitInstructionPool(this);
        _dirty = true;
    }
}

InstructionsPool::Node InstructionsPool::createNode(int priority, Instruction* instruction) {
    auto node = Node();
    node.insert(std::make_pair(priority, instruction));
    return node;
}

void InstructionsPool::check() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (!_queue->empty()) {
        auto instruction = _queue->top().begin()->second;
        if (instruction->willServe()) {
            CC_SAFE_RETAIN(this);
            _state = State::Worked;
            auto finish = instruction->getFinishTask();
            finish->continueWithBlock([&](Instruction::Task* task) -> Instruction::Task* {
                auto instruction = task->result();
                instruction->end();
                this->check();
                CC_SAFE_RELEASE(instruction);
                CC_SAFE_RELEASE(this);
                return nullptr;
            });
            instruction->begin();
            _queue->pop();
        }
    } else {
        if (delegate != nullptr)
            delegate->didFreeInstructionPool(this);
        _dirty = false;
        _state = State::Wait;
    }
}

void InstructionsPool::commit() {
    if (_state == State::Wait)
        check();
}
