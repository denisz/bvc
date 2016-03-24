//
//  BFExecutor.hpp
//  Bolts
//
//  Created by denis zaytcev on 2/11/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef BFExecutor_hpp
#define BFExecutor_hpp

#include "ThreadPool.hh"
#include "Scheduler.hh"
#include "AIRef.h"

using namespace TaskManager;

namespace Bolts {
    class BFThreadPool: public internal::AIRef, public ThreadPool {
    public:
        BFThreadPool(unsigned int nbThreads, ThreadManager& manager)
        : ThreadPool(nbThreads, manager){
            
        }
    };
    
    class BFSheduler: public internal::AIRef, public Scheduler {
    public:
        BFSheduler(unsigned int nbThreads, ThreadManager& manager)
        : Scheduler(nbThreads, manager){
            
        }
    };
    
    class BFExecutor: public internal::AIRef {
    private:
        ThreadManager* _manager;
        BFThreadPool* _threadPool;
        BFSheduler* _threadSheduler;
        static std::mutex _lock;
        static BFExecutor* _defaultExecutor;
    public:
        BFExecutor(uint thCount = 1, uint tCount = 3);
        ~BFExecutor();
        BFThreadPool* pool();
        BFThreadPool* createPool(uint tCount = 3);
        BFSheduler* sheduler();
        BFSheduler* createSheduler(uint tCount = 3);
        
        static BFExecutor* defaultExecutor (uint thCount = 1, uint tCount = 3) {
            std::lock_guard<std::mutex> lock(_lock);
            if (BFExecutor::_defaultExecutor == nullptr) {
                BFExecutor::_defaultExecutor = new BFExecutor(thCount, tCount);
            }
            
            return BFExecutor::_defaultExecutor;
        }
    };
}

#endif /* BFExecutor_hpp */
