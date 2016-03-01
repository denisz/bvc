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

namespace common {
    const std::string PATH_GLOBAL = "*";
    
    class Router: public internal::AIRef {
    public:
        typedef std::function<void(internal::network::Response*)> Handler;
    private:
        struct HandlerData
        {
            HandlerData():handler(nullptr), path(""){}
            std::string path;
            Handler handler;
        };
        
    private:
        std::forward_list<HandlerData> _handlers;
        std::forward_list<HandlerData> _after_handlers;
        std::forward_list<HandlerData> _before_handlers;
        
        void worker(std::forward_list<HandlerData>& handlers, internal::network::Response& res);
        Router();
    public:
        ~Router();
        Router* command(const std::string& path, const Handler& handler);
        Router* action(const std::string& path, const Handler& handler);
        Router* after(const std::string& path, const Handler& handler);
        Router* before(const std::string& path, const Handler& handler);
        
        void process(internal::network::Response& res);
        void error(internal::network::Response& res);
        
        virtual bool init();
        static Router* create();
    };
}

#endif /* Router_hpp */
