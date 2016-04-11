//
//  InstructionBlock.cpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#include "InstructionBlock.hpp"

using namespace Instructions;


InstructionBlock* InstructionBlock::createWithBlock(Block block) {
    auto ref = new InstructionBlock();
    if (ref->init()) {
        ref->_block = block;
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}


void InstructionBlock::serve() {
    if (_block) {
        _block(this);
    } else {
        complete();
    }
    
    
}