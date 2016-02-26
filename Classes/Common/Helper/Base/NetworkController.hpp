//
//  NetworkController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef NetworkController_hpp
#define NetworkController_hpp

#include <stdio.h>
#include "IReactionController.hpp"
#include "ICommandController.hpp"

namespace game {
    class NetworkController: public internal::AIRef, public IReactionController, public ICommandController {
    protected:
        virtual bool init();
    };
}
#endif /* NetworkController_hpp */
