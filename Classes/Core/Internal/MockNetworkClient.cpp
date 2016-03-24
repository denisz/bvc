//
//  MockNetworkClient.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/12/16.
//
//

#include "MockNetworkClient.hpp"

using namespace internal;

MockNetworkClient* MockNetworkClient::createWithFile(const std::string& filename) {
    auto ref = new MockNetworkClient();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool MockNetworkClient::initWithFileName(const std::string& filename) {
    return true;
}