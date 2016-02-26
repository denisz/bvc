//
//  SessionController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef SessionController_hpp
#define SessionController_hpp


#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class SessionController: public internal::AIRef, public ICommandController {
    public:
        bool isAuthenticated();
        CommandRunner::Handler* checkSessionTokenAsync();
        virtual bool init();
        BV_CREATE_FUNC(SessionController);
    };
}



#endif /* SessionController_hpp */
