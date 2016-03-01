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
#include "GameConfig.hpp"
#include "Localized.hpp"
#include "Storage.hpp"
#include "NetworkClient.hpp"
#include "ActionsClient.hpp"
#include "WebSocketTransport.hpp"
#include "AwesomeCache.hpp"
#include "EventuallyRequests.hpp"
#include "FileUtils.hpp"


using namespace internal::network;
using namespace internal;
using namespace common;

class ServiceLocator {
private:
    static NetworkClient*       _networkClient;
    static Storage*             _storage;
    static AwesomeCache*        _cache;
    static EventuallyRequests*  _eventually;
    static ActionsClient*       _actionsClient;
    
    static bool isCreated;
public:
    static void create();
    
    static NetworkClient*       network();
    static Storage*             storage();
    static AwesomeCache*        cache();
    static EventuallyRequests*  eventually();
    static ActionsClient*       actionsClient();
};

#endif /* ServiceLocator_hpp */
