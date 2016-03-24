//
//  MockNetworkClient.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/12/16.
//
//

#ifndef MockNetworkClient_hpp
#define MockNetworkClient_hpp

#include "stdafx.h"
#include "NetworkClient.hpp"

namespace internal {
    class MockNetworkClient: public AIRef {
    private:
        virtual bool init();
    public:
        static MockNetworkClient* createWithFile(const std::string& filename);
    };
}

#endif /* MockNetworkClient_hpp */
