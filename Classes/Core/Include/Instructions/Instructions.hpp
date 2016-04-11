//
//  Instructions.hpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef Instructions_hpp
#define Instructions_hpp

#include "Bolts.hpp"
#include "InstructionsPool.hpp"
#include "Instruction.hpp"
#include "InstructionBlock.hpp"
#include <string>


namespace Instructions {
    class InstructionsPool;
    class Instruction;
    class InstructionBlock;
    
    class Instructions {
    public:
        const std::string version() {
            return "0.0.1";
        }
    };
    
}


#endif /* Instructions_hpp */
