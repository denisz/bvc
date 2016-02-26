//
//  EventuallyRequests.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/15/16.
//
//

#ifndef EventuallyRequests_hpp
#define EventuallyRequests_hpp

#include "stdafx.h"
#include "Response.hpp"
#include "Request.hpp"
#include "FileUtils.hpp"

namespace common {
    class EventuallyRequests {
    private:
        std::string generateFileName(internal::network::Request &req);
        EventuallyRequests();
    public:
        typedef Bolts::BFTask<Bolts::BFBool>* HandlerEventually;
        
        class Events: public  BaseObserverProtocol {
        public:
            virtual void onDefferedRequest(internal::network::Response *res) {};
            virtual void onDefferedError(internal::network::Response *res) {};
        };
    public:
        
        bool deferredRequest(internal::network::Request &req);
        HandlerEventually process();
        static EventuallyRequests* create();
    };
}

#endif /* EventuallyRequests_hpp */
