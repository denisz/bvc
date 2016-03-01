//
//  BFExecutor.cpp
//  Bolts
//
//  Created by denis zaytcev on 2/11/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#include "BFExecutor.hpp"

using namespace Bolts;
std::mutex BFExecutor::_lock;
BFExecutor* BFExecutor::_defaultExecutor;

BFExecutor::BFExecutor(uint thCount, uint tCount) {
    _manager        = new ThreadManager(thCount);
    _threadPool     = new BFThreadPool(tCount, *_manager);
    _threadSheduler = new BFSheduler(tCount, *_manager);
}

BFThreadPool* BFExecutor::pool(){
    return _threadPool;
}

BFSheduler* BFExecutor::sheduler() {
    return _threadSheduler;
}

BFThreadPool* BFExecutor::createPool(uint tCount) {
    return new BFThreadPool(tCount, *_manager);
}

BFSheduler* BFExecutor::createSheduler(uint tCount) {
    return new BFSheduler(tCount, *_manager);
}

BFExecutor::~BFExecutor() {
//    CC_SAFE_DELETE(_manager);
//    CC_SAFE_DELETE(_threadPool);
}