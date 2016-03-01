//
//  ActionsClient.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#ifndef ActionsClient_hpp
#define ActionsClient_hpp

#include "stdafx.h"

namespace internal {
    class ActionsClient: public AIRef {
    public:
        class Event: public internal::AIRef {
        private:
            std::string _cmd;
            internal::BVValueMap _object;
        public:
            Event() {}
            
            std::string command() {
                return _cmd;
            }
            
            bool initWithCommand (const std::string& cmd) {
                _cmd = cmd;
                return true;
            }
            
            void setObject(internal::BVValueMap& object) {
                _object = object;
            }
            
            internal::BVValueMap& object() {
                return _object;
            }
            
            static Event* createWithCommand(const std::string& cmd) {
                auto ref = new Event();
                if (ref->initWithCommand(cmd)) {
                    return ref;
                }
                
                CC_SAFE_DELETE(ref);
                return nullptr;
            }
        };
    public:
        class Events: public  BaseObserverProtocol {
        public:
            virtual void onCall(Event* event) {};
        };
    private:
        virtual bool init();
    public:
        void call(Event* event);
        Event* createEventWithCommand(const std::string& cmd);
        static ActionsClient* create();
    };
}

#endif /* ActionsClient_hpp */
