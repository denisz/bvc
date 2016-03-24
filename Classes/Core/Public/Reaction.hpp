//
//  BaseReaction.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef Reaction_hpp
#define Reaction_hpp

#include "stdafx.h"
#include <stdio.h>
#include "NetworkClient.hpp"

using namespace internal::network;

namespace common
{
    class Reaction: public internal::AIRef, public NetworkClient::Events {
    public:
        class Delegate {
        public:
            virtual void processMessage(Response &res)  =0;
            virtual void processError(Response &res)    =0;
            virtual void processClose()                 =0;
            virtual void processOpen()                  =0;
            virtual void didSubscribe()                 =0;
            virtual void didUnsubscribe()               =0;
        };
        
    private:
        bool _flagMultiThread = true;
        
        virtual void onError(Response *res);
        virtual void onReceivedMessage(Response *res);
        virtual void onOpen();
        virtual void onClose();
        
        void handlerReceivedMessage(Response *res);
        void handlerErrorMessage(Response *res);
        Bolts::BFThreadPool* _threadPool;
        
        Reaction();
    public:
        ~Reaction();
        Delegate* delegate;
        
        virtual bool init();
        void subscribe();
        void unsubscribe();
        
        void setMode(bool multiThread);
        
        void pause();
        void resume();
        void stop();
        
        static Reaction* create();
        static Reaction* createWithDelegate(Delegate* delegate);
    };
}

#endif /* Reaction_hpp */
