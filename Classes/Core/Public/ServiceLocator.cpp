//
//  ServiceLocator.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "ServiceLocator.hpp"

using namespace internal::network;
using namespace common;

bool ServiceLocator::isCreated = false;

NetworkClient* ServiceLocator::_networkClient;
Storage* ServiceLocator::_storage;
AwesomeCache* ServiceLocator:: _cache;
EventuallyRequests* ServiceLocator::_eventually;

void ServiceLocator::create() {
    if (ServiceLocator::isCreated) return;
    ServiceLocator::isCreated = true;

    FileUtils::sharedInstance()->load();
    
    auto transport = WebSocketTransport::create();
    _networkClient = NetworkClient::createWithTransport(transport);
    
    _storage = Storage::create();
    
    _eventually = EventuallyRequests::create();
    
    _cache = AwesomeCache::create();
}

NetworkClient* ServiceLocator::network() {
    return ServiceLocator::_networkClient;
}

Storage* ServiceLocator::storage() {
    return ServiceLocator::_storage;
}

AwesomeCache* ServiceLocator:: cache() {
    return ServiceLocator::_cache;
}
