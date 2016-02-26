//
//  BotsController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef BotsController_hpp
#define BotsController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class BotsController: public internal::AIRef, public ICommandController {
    public:
        CommandRunner::Handler* getAsync();
        
        virtual bool init();
        BV_CREATE_FUNC(BotsController);
    };

}

#endif /* BotsController_hpp */
