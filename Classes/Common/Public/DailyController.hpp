//
//  DailyController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#ifndef DailyController_hpp
#define DailyController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class DailyController: public internal::AIRef, public ICommandController {
    public:
        
        CommandRunner::Handler* getAsync();
        virtual bool init();
        BV_CREATE_FUNC(DailyController);
    };
}


#endif /* DailyController_hpp */
