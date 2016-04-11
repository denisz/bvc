//
//  Observable.h
//  bvunity
//
//  Created by denis zaytcev on 3/25/16.
//
//

#ifndef Observable_h
#define Observable_h

#include "stdafx.h"
#include <map>
#include <vector>
#include <memory>
#include <set>

namespace internal {
    template <typename T>
    class InnerObserverContainer {
    public:
        std::set<T*> observers;
        
        void addObserver(T* obs) {
            observers.insert(obs);
        }
        
        void removeObserver(BaseObserverProtocol* observer) {
            observers.erase(static_cast<T*>(observer));
        }
        
        void clear() {
            observers.clear();
        }
    };
    
    
    template <class P>
    class Observable {
    public:
        std::mutex _observable_mutex;
        InnerObserverContainer<P> _observerContainer;
        
        // P stands for current protocol (a group of parametrized events)
        // O is a class, overriding some of the protocol's methods, this defining it's reaction to events
        void listen(P* observer) {
            std::lock_guard<std::mutex> lock(_observable_mutex);
            if (!observer) {
                return;
            }
            
            _unsubscribeMap.insert(std::make_pair(observer->P::observerId, true));
            _observerContainer.addObserver(static_cast<P*>(observer));
        }
        
        // to disambiguate a call to overloaded member function
        // use notify(static_cast<void (Class::*)(T1, T2, ...)>(&Class::method), arg1, arg2, ...);
        template <typename... MethodArgumentTypes, typename... ActualArgumentTypes>
        void notify(void (P::*method)(MethodArgumentTypes...), ActualArgumentTypes... args) {
            _observable_mutex.lock();
            std::vector<P*> currentObservers;
            std::copy(std::begin(_observerContainer.observers), std::end(_observerContainer.observers), std::back_inserter(currentObservers));
            _observable_mutex.unlock();
            std::vector<unsigned int> currentObserverIds;
            for (unsigned int i = 0; i < currentObservers.size(); i++) {
                currentObserverIds.push_back(currentObservers[i]->observerId);
            }
            for (unsigned int i = 0; i < currentObservers.size(); i++) {
                if (_unsubscribeMap.find(currentObserverIds[i]) == std::end(_unsubscribeMap)) {
                    continue;
                }
                (currentObservers[i]->*method)(args...);
            }
        }
        
        void stopListening(P* observer) {
            std::lock_guard<std::mutex> lock(_observable_mutex);
            
            if (!observer) {
                return;
            }
            auto observerId = observer->P::observerId;
            if (_unsubscribeMap.find(observerId) == std::end(_unsubscribeMap)) {
                return;
            }
            _unsubscribeMap.erase(observerId);
        }
        
        void clearObserver() {
            std::lock_guard<std::mutex> lock(_observable_mutex);
            _observerContainer.clear();
            _unsubscribeMap.clear();
        }
    private:
        std::map<int, bool> _unsubscribeMap;
    public:
        Observable() {
            _unsubscribeMap      = std::map<int, bool>();
            _observerContainer  = InnerObserverContainer<P>();
        };
        ~Observable() {
            clearObserver();
        };
    };
}

#endif /* Observable_h */
