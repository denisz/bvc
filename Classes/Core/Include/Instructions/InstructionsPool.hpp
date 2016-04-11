//
//  InstructionsPool.hpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef InstructionsPool_hpp
#define InstructionsPool_hpp

#include <map>
#include <stdio.h>
#include "AIRef.h"
#include "Instruction.hpp"


namespace  Instructions {
    class InstructionsPool: public internal::AIRef {
    public:
        typedef int Priority;
        typedef std::map<int, Instruction*> Node;
        enum class State {Wait, Worked};
        class Delegate {
        public:
            virtual void didFreeInstructionPool(InstructionsPool* pool) = 0;
            virtual void didWaitInstructionPool(InstructionsPool* pool) = 0;
        };
    private:
        std::mutex _mutex;
        std::priority_queue<Node>* _queue;
        Instruction* _current;
        State _state;
        bool _dirty;
    private:
        void check();
        Node createNode(int, Instruction* instruction);
    public:
        InstructionsPool();
        ~InstructionsPool();
        
        Delegate* delegate;
        
        bool init();
        void commit();
        void addInstruction(int, Instruction* instruction);
        
        static InstructionsPool* create();
    };
}

#endif /* InstructionsPool_hpp */
