//
//  GCD.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/14/16.
//
//

#ifndef GCD_hpp
#define GCD_hpp

#include "stdafx.h"
#include "cocos2d.h"

namespace internal {
    class GCD {
    public:
        typedef std::function<void()> Message;
    private:
        std::list<Message>* _UIWsMessageQueue;
        std::mutex   _UIWsMessageQueueMutex;
        void _sendMessageToUIThread(Message msg);
        GCD();
    public:
        GCD(GCD const&)             = delete;
        void operator=(GCD const&)  = delete;
        
        void update(float dt);
        
        static GCD& sharedInstance();
        static void sendMessageToUIThread(Message msg);
    };
}

#endif /* GCD_hpp */
