//
//  Actions.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#ifndef ActionsRouter_hpp
#define ActionsRouter_hpp

#include "stdafx.h"
#include "ActionsClient.hpp"

namespace common {
    const std::string PATH_GLOBAL_ACTION = "*";
    
    class ActionsRouter: public internal::AIRef {
    public:
        typedef std::function<void(internal::ActionsClient::Event*)> Handler;
    private:
        class Delegate {};
        
        struct HandlerData
        {
            HandlerData():handler(nullptr), path(""){}
            std::string path;
            Handler handler;
        };
        
    private:
        std::mutex _mutex;
        std::forward_list<HandlerData> _handlers;
        bool _enabled;
        void setEnabled(bool value);
        ActionsRouter();
    public:
        ~ActionsRouter();
        ActionsRouter* action(const std::string& path, const Handler& handler);
        
        Delegate* delegate;
        
        void pause();
        void resume();
        void stop();

        
        void process(internal::ActionsClient::Event* event);
        virtual bool init();
        
        static ActionsRouter* create();
    };
}

#endif /* ActionsRouter_hpp */
