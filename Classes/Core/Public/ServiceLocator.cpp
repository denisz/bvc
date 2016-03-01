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
ActionsClient*  ServiceLocator::_actionsClient;

void ServiceLocator::create() {
    if (ServiceLocator::isCreated) return;
    ServiceLocator::isCreated = true;

    GameConfig::sharedInstance()->load();
    GameConfig::sharedInstance()->loadFilePaths();
    Localized::load();
    
    FileUtils::sharedInstance()->load();
    
    auto transport = WebSocketTransport::create();
    _networkClient = NetworkClient::createWithTransport(transport);
    
    _storage = Storage::create();
    
    _eventually = EventuallyRequests::create();
    
    _cache = AwesomeCache::create();
    
    _actionsClient = ActionsClient::create();
}

NetworkClient* ServiceLocator::network() {
    return ServiceLocator::_networkClient;
}

ActionsClient* ServiceLocator::actionsClient() {
    return ServiceLocator::_actionsClient;
}

EventuallyRequests*  ServiceLocator::eventually() {
    return ServiceLocator::_eventually;
}

Storage* ServiceLocator::storage() {
    return ServiceLocator::_storage;
}


AwesomeCache* ServiceLocator:: cache() {
    return ServiceLocator::_cache;
}
