//
//  ServiceLocator.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef ServiceLocator_hpp
#define ServiceLocator_hpp

#include "stdafx.h"
#include "Storage.hpp"
#include "NetworkClient.hpp"
#include "WebSocketTransport.hpp"
#include "AwesomeCache.hpp"
#include "EventuallyRequests.hpp"
#include "FileUtils.hpp"


using namespace internal::network;
using namespace common;

class ServiceLocator {
private:
    static NetworkClient*       _networkClient;
    static Storage*             _storage;
    static AwesomeCache*        _cache;
    static EventuallyRequests*  _eventually;
    
    static bool isCreated;
public:
    static void create();
    
    static NetworkClient* network();
    static Storage* storage();
    static AwesomeCache* cache();
    static EventuallyRequests* eventually();
};

#endif /* ServiceLocator_hpp */
