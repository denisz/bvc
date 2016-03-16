//
//  BFTask.hpp
//  Bolts
//
//  Created by denis zaytcev on 2/10/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef BFTask_hpp
#define BFTask_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include "BFExecutor.hpp"
#include "AIRef.h"

namespace Bolts {
    enum class BFError {NONE, TIMEOUT, DISCONNECT, EMPTY, UNKNOWN};
    
    template<class T>
    class BFTask: public internal::AIRef {
    public:
        typedef std::function<BFTask<T>*(BFTask<T>*)> BFTaskHandler;
        typedef std::function<void()> BFTaskWorker;
    private:
        bool _cancelled;
        bool _completed;
        std::mutex _mutex;

        std::vector<BFTaskWorker> _callbacks;
        bool _isContinue = false;
        T* _result;
        BFError _error;
        void runContinuations();
        void worker(const BFTaskHandler &block);
    public:
        BFTask();
        ~BFTask();
        BFTask<T>* _continueTask;
        
        static BFTask<T>* taskWithResult(T &result);
        static BFTask<T>* taskWithError(BFError &error);
        static BFTask<T>* cancelledTask();

        bool trySetResult(T &result);
        bool trySetError(const BFError &error);
        bool trySetCancelled();
        bool isCompleted();
        
        bool hasError();
        
        T* result();
        BFError error();
        
        BFTask<T>* continueWithSuccessBlock(const BFTaskHandler &block);
        BFTask<T>* continueWithBlock(const BFTaskHandler &block);
        bool init();
        static BFTask<T>* create();
    };

    template<class T>
    BFTask<T> ::BFTask()
    : _result(nullptr)
    , _error(BFError::NONE)
    , _cancelled(false)
    , _completed(false)
    , _continueTask(nullptr){
        _callbacks = std::vector<BFTaskWorker>();
    }

    template<class T>
    BFTask<T> ::~BFTask() {
        CC_SAFE_RELEASE_NULL(_result);
        CC_SAFE_RELEASE_NULL(_continueTask);
        _callbacks.clear();
    }
    
    template<class T>
    BFTask<T>* BFTask<T> ::create() {
        auto task = new BFTask<T>();
        if (task->init()){
            return task;
        } else {
            delete task;
            task = nullptr;
            return nullptr;
        }
    }
    
    template<class T>
    bool BFTask<T> ::init() {
        return true;
    }
    
    template<class T>
    bool BFTask<T> ::hasError() {
        return _error != BFError::NONE;
    }

    template<class T>
    BFTask<T>* BFTask<T> ::cancelledTask() {
        auto task = new BFTask<T>();
        task->trySetCancelled();
        return task;
    }

    template<class T>
    BFTask<T>* BFTask<T> ::taskWithResult(T &result) {
        auto task = new BFTask<T>();
        task->trySetResult(result);
        return task;
    }

    template<class T>
    BFTask<T>* BFTask<T> ::taskWithError(BFError &error) {
        BFTask<T>* task = new BFTask<T>();
        task->trySetError(error);
        return task;
    }


    template<class T>
    BFTask<T>* BFTask<T> ::continueWithBlock(const BFTaskHandler &block) {
        std::lock_guard<std::mutex> lock(_mutex);
        
        bool completed;

        if (_isContinue == false) {
            _continueTask = BFTask<T>::create();
            _isContinue = true;
        }

        //вернуть новый таск
        completed = isCompleted();
        if (!completed) {
            _callbacks.push_back(std::bind(&BFTask<T>::worker, this, block));
        }
        
        _mutex.unlock();
        
        if (completed) {
            CC_SAFE_RETAIN(this);
            worker(block);
        }
        
        return _continueTask;
    }
    
    template<class T>
    BFTask<T>* BFTask<T>::continueWithSuccessBlock(const BFTaskHandler &_block) {
        return continueWithBlock([&](BFTask<T> *task) -> BFTask<T>* {
            if (!task->hasError()) {
                return _block(task);
            }
            
            return task;
        });
    }

    template<class T>
    bool BFTask<T> ::isCompleted() {
        return _completed;
    }

    template<class T>
    bool BFTask<T> ::trySetError(const BFError &error) {
        std::lock_guard<std::mutex> lock(_mutex);
        
        if (_completed) {
            return false;
        }
        _completed = true;

        _error = error;
        runContinuations();
        return true;
    }
    
    template<class T>
    void BFTask<T>::worker(const BFTaskHandler &block) {
        BFTask<T>* resultTask;
        
        try {
            resultTask = block(this);
        } catch(const std::exception& e) {
            
        }
        
        auto continueWithTask = [](BFTask<T>* _ct, BFTask<T>* task) {
            if (_ct != nullptr) {
                if (!task->hasError()) {
                    auto result = task->result();
                    _ct->trySetResult(*result);
                } else {
                    auto error = task->error();
                    _ct->trySetError(error);
                }
            }
            
            CC_SAFE_RELEASE(task);
        };
        
        if (resultTask != nullptr) {
            if (resultTask->isCompleted()) {
                continueWithTask(this->_continueTask, resultTask);
            } else {
                resultTask->continueWithBlock([&](BFTask<T> *task) -> BFTask<T>* {
                    continueWithTask(this->_continueTask, task);
                    return nullptr;
                });
            }
        } else {
            continueWithTask(this->_continueTask, this);
        }
    }

    template<class T>
    bool BFTask<T> ::trySetResult(T &result) {
        std::lock_guard<std::mutex> lock(_mutex);
        
        if (_completed) {
            return false;
        }

        _completed = true;
        _result = &result;
        
        CC_SAFE_RETAIN(&result);
        
        runContinuations();
        return true;
    }

    template<class T>
    bool BFTask<T> ::trySetCancelled() {
        std::lock_guard<std::mutex> lock(_mutex);
        
        _cancelled = true;
        _completed = true;
        return true;
    }

    template<class T>
    T* BFTask<T> ::result() {
        return _result;
    }

    template<class T>
    BFError BFTask<T> ::error() {
        return _error;
    }

    template<class T>
    void BFTask<T> ::runContinuations() {
        auto pool = BFExecutor::defaultExecutor()->pool();
        
        for (auto worker: _callbacks) {
            CC_SAFE_RETAIN(this);
            pool->addTask(worker);
        }
        
        _callbacks.clear();
    }
}

#endif /* BFTask_hpp */
