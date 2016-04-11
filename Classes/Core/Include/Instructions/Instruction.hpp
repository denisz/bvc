//
//  Instruction.hpp
//  Bolts
//
//  Created by denis zaytcev on 4/8/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef Instruction_hpp
#define Instruction_hpp

#include <stdio.h>
#include "AIRef.h"
#include "Bolts.hpp"

namespace  Instructions {
    class Instruction: public internal::AIRef {
    public:
        typedef Bolts::BFTask<Instruction> Task;
        typedef Bolts::BFTaskCompletionSource<Instruction> Promise;
        typedef std::function<Task*(Task*)> TaskHandler;
    private:
        Task* _finishTask;
        Promise* _promise;
    public:
        Instruction();
        ~Instruction();
        Instruction* continueWithBlock(const TaskHandler &block);
        Task* getFinishTask();
        
        void end();
        void begin();
        bool init();
        void update();
        void complete();
        
        virtual void serve();
        virtual bool willServe();
    public:
        friend class InstructionsPool;
    };
}

#endif /* Instruction_hpp */
