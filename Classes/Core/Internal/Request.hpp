//
//  Request.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef Request_hpp
#define Request_hpp

#include "stdafx.h"
#include "Coder.hpp"

namespace internal {
    namespace network {
        class Request: public internal::AIRef {
        public:
            Request();
            time_t timestamp;
            rapidjson::Document out;
            const std::string outReadyMessage();
        };
    }
}
#endif /* Request_hpp */
