//
//  UserController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef UserController_hpp
#define UserController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class UserController: public internal::AIRef, public ICommandController {
    public:
        CommandRunner::Handler* getAsync(const std::string& profileId, bool extended = false);
        
        virtual bool init();
        BV_CREATE_FUNC(UserController);
    };
}

#endif /* UserController_hpp */
