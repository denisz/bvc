//
//  InstructionBlock.hpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef InstructionBlock_hpp
#define InstructionBlock_hpp

#include <stdio.h>
#include "Instruction.hpp"


namespace Instructions {
    class InstructionBlock: public Instruction {
    public:
        typedef std::function<void(Instruction* instruction)> Block;
    private:
        virtual void serve();
        Block _block;
    public:
        static InstructionBlock* createWithBlock(Block block);
    };
}
#endif /* InstructionBlock_hpp */
