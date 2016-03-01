//
//  Actions.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#ifndef Actions_hpp
#define Actions_hpp

#include "stdafx.h"
#include "ActionsClient.hpp"

namespace common {
    class Actions: public internal::AIRef, public internal::ActionsClient::Events {
    public:
        class Delegate {
        public:
            virtual void processAction(internal::ActionsClient::Event* event) {};
        };
    private:
        virtual void onCall(internal::ActionsClient::Event* event);
        Actions();
    public:
        ~Actions();
        Delegate* delegate;
        
        bool init();
        void subscribe();
        void unsubscribe();
        
        static Actions* create();
        static Actions* createWithDelegate(Delegate* delegate);
    };
}

#endif /* Actions_hpp */
