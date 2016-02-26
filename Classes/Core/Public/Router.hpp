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
#include <stdio.h>
#include "Response.hpp"

namespace common {
    const std::string PATH_GLOBAL = "*";
    
    class Router: public internal::AIRef {
    public:
        typedef std::function<void(internal::network::Response*)> routerHandler;
    private:
        struct Handler
        {
            Handler():handler(nullptr), path(""){}
            std::string path;
            routerHandler handler;
        };
        
    private:
        std::vector<Handler> _handlers;
        std::vector<Handler> _after_handlers;
        std::vector<Handler> _before_handlers;
        
        void worker(std::vector<Handler>& handlers, internal::network::Response& res);
        Router();
    public:
        ~Router();
        void command(const std::string& path, const routerHandler& handler);
        void after(const std::string& path, const routerHandler& handler);
        void before(const std::string& path, const routerHandler& handler);
        
        void process(internal::network::Response& res);
        void error(internal::network::Response& res);
        
        virtual bool init();
        static Router* create();
    };
}

#endif /* Router_hpp */
