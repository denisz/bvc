//
//  Router.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef Router_hpp
#define Router_hpp

#include "stdafx.h"
#include "Response.hpp"

using namespace internal::network;

namespace common {
    const std::string PATH_GLOBAL = "*";
    
    class Router: public internal::AIRef {
    public:
        typedef std::function<bool(internal::network::Response*)> Handler;
        typedef std::vector<Handler> HandlerList;
        typedef std::map<std::string, HandlerList> Handlers;
    private:
        class Delegate {
            virtual void doesNotInvocation(const std::string& path) {};
        };
        
    private:
        std::mutex _mutex;
        Handlers _handlers;
        
        bool _enabled;
        void setEnabled(bool value);
        
        void worker(Handlers& handlers, const std::string& command, Response& res);
        Router();
    public:
        ~Router();
        
        Delegate* delegate;
        
        Router* command(const std::string& path, const Handler& handler);
        Router* command(const std::string& path, std::initializer_list<Handler> handler);
        Router* use(Handlers& handlers);
        
        void process(internal::network::Response& res);
        void error(internal::network::Response& res);
        
        void pause();
        void resume();
        void stop();
        
        virtual bool init();
        static Router* create();
    };
}

#endif /* Router_hpp */
