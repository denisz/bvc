//
//  sCompletionSource.hpp
//  Bolts
//
//  Created by denis zaytcev on 2/10/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef BFTaskCompletionSource_hpp
#define BFTaskCompletionSource_hpp

#include <stdio.h>
#include <iostream>
#include "BFTask.hpp"
#include "AIRef.h"

namespace Bolts {

class BFString: public internal::AIRef {
public:
    std::string value;
    BFString(std::string& message){
        value = message;
    }
};
class BFInt: public internal::AIRef {
public:
    int value;
    BFInt(int number){
        value = number;
    }
};
class BFBool: public internal::AIRef {
public:
    bool value;
    BFBool(bool result){
        value = result;
    }
};
    
template<class T>
    class BFTaskCompletionSource: public internal::AIRef   {
    private:
        BFTask<T>* _task;
        bool init();
        BFTaskCompletionSource(uint countThread);
    public:
        ~BFTaskCompletionSource();

        BFTask<T>* task();
        uint countThread = 1;
        
        void setResult(T &result);
        void setError(const  BFError &error);
        
        bool isCompleted();
        
        void cancel();
        bool trySetResult(T& result);
        bool trySetError(const BFError &error);
        
        static BFTaskCompletionSource<T>* taskCompletionSource(uint countThread = 1);
    };

    template<class T>
    BFTaskCompletionSource<T> ::BFTaskCompletionSource(uint countThread) {
        _task = BFTask<T>::create();
    }

    template<class T>
    BFTaskCompletionSource<T>* BFTaskCompletionSource<T> ::taskCompletionSource(uint countThread) {
        auto task = new BFTaskCompletionSource<T>(countThread);
        if (task->init()){
            return task;
        } else {
            delete task;
            task = nullptr;
            return nullptr;
        }
    }
    
    template<class T>
    BFTaskCompletionSource<T>::~BFTaskCompletionSource() {
        CC_SAFE_RELEASE(_task);
    }
    
    template<class T>
    bool BFTaskCompletionSource<T> ::init() {
        return true;
    }

    template<class T>
    BFTask<T>* BFTaskCompletionSource<T> ::task() {
        return _task;
    }
    
    template<class T>
    bool BFTaskCompletionSource<T> ::isCompleted() {
        return _task->isCompleted();
    }

    template<class T>
    void BFTaskCompletionSource<T> ::setError(const BFError &error) {
        if (!trySetError(error)) {
            std::cout << "Error " << std::endl;
        }
    }

    template<class T>
    void BFTaskCompletionSource<T> ::setResult(T &result){
        if (!trySetResult(result)) {
            std::cout << "Error " << std::endl;
        }
    }

    template<class T>
    void BFTaskCompletionSource<T> :: cancel() {
        if (!_task->trySetCancelled()) {
            std::cout << "Error " << std::endl;
        }
    }

    template<class T>
    bool BFTaskCompletionSource<T> ::trySetResult(T &result) {
        return _task->trySetResult(result);
    }

    template<class T>
    bool BFTaskCompletionSource<T> ::trySetError(const BFError &error) {
        return _task->trySetError(error);
    }
}

#endif /* BFTaskCompletionSource_hpp */
