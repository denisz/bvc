//
//  BFTaskCompletionAfter.hpp
//  Bolts
//
//  Created by denis zaytcev on 2/12/16.
//
//

#ifndef BFTaskCompletionAfter_hpp
#define BFTaskCompletionAfter_hpp

#include <stdio.h>
#include <iostream>
#include "BFTask.hpp"
#include "AIRef.h"

namespace Bolts {
    template<class T>
    class BFTaskVector: public internal::AIRef, public std::vector<T> {};
    
    template<class T>
    class BFTaskCompletionAfter: public internal::AIRef  {
    public:
    private:
        BFTask<T>* _task;
        uint _counter;
        uint _maxCounter;
        BFTaskVector<T> _results;
        bool _completed;
        std::mutex _mutex;
        BFTaskCompletionSource<BFTaskVector<T>>* _promise;
        bool initWithCounter(uint count);
        BFTaskCompletionAfter(uint countThread);
    public:
        ~BFTaskCompletionAfter();
        BFTask<BFTaskVector<T>>* task();

        void setResult(T &result);
        void setError(const BFError &error);
        
        bool isCompleted();
        
        void cancel();
        bool trySetResult(T& result);
        bool trySetError(const BFError &error);
        
        static BFTaskCompletionAfter<T>* taskAfter(uint counter, uint countThread = 1);
    };
    
    template<class T>
    BFTaskCompletionAfter<T> ::BFTaskCompletionAfter(uint countThread)
    : _counter(0)
    , _promise(nullptr)
    , _completed(false)
    , _maxCounter(0) {
        _task = BFTask<T>::create();
        _task->countThread = countThread;
    }
    
    template<class T>
    BFTaskCompletionAfter<T>* BFTaskCompletionAfter<T> ::taskAfter(uint counter, uint countThread) {
        auto task = new BFTaskCompletionAfter<T>(countThread);
        if (task->initWithCounter(counter)){
            return task;
        } else {
            delete task;
            task = nullptr;
            return nullptr;
        }
    }
    
    template<class T>
    BFTaskCompletionAfter<T>::~BFTaskCompletionAfter() {
        for (auto result: _results) {
            CC_SAFE_RELEASE(&result);
        }
        
        CC_SAFE_RELEASE_NULL(_task);
        CC_SAFE_RELEASE_NULL(_promise);
        
        _results.clear();
    }
    
    template<class T>
    bool BFTaskCompletionAfter<T> ::initWithCounter(uint count) {
        _counter = 0;
        _maxCounter = count;
        _results = BFTaskVector<T>();
        _promise = BFTaskCompletionSource<BFTaskVector<T>>::taskCompletionSource();
        return true;
    }
    
    template<class T>
    BFTask<BFTaskVector<T>>* BFTaskCompletionAfter<T> ::task() {
        return _promise->task();
    }
    
    template<class T>
    bool BFTaskCompletionAfter<T> ::isCompleted() {
        return _completed;
    }
    
    template<class T>
    void BFTaskCompletionAfter<T> ::setError(const BFError &error) {
        if (!trySetError(error)) {
            std::cout << "Error " << std::endl;
        }
    }
    
    template<class T>
    void BFTaskCompletionAfter<T> ::setResult(T &result){
        if (!trySetResult(result)) {
            std::cout << "Error " << std::endl;
        }
    }
    
    template<class T>
    void BFTaskCompletionAfter<T> ::cancel() {
        if (!_task->trySetCancelled()) {
            std::cout << "Error " << std::endl;
        }
    }
    
    template<class T>
    bool BFTaskCompletionAfter<T> ::trySetResult(T &result) {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_completed) {
            return false;
        }
        
        _counter += 1;
        _results.push_back(result);
        CC_SAFE_RETAIN(&result);
        
        if (_counter == _maxCounter) {
            _completed = true;
            return _promise->trySetResult(_results);
        }
        
        return false;
    }
    
    template<class T>
    bool BFTaskCompletionAfter<T> ::trySetError(const BFError &error) {
        return false;
    }
}
#endif /* BFTaskCompletionSource_hpp */
