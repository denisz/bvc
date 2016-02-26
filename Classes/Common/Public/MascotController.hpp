//
//  MascotController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/24/16.
//
//

#ifndef MascotController_hpp
#define MascotController_hpp

#include "stdafx.h"
#include "DataSourceController.hpp"

using namespace common;

namespace game {
    class MascotController: public DataSourceController {
    public:
        CommandRunner::Handler* getAsync();
        CommandRunner::Handler* exchange(const std::string& mascotId);
        
        virtual bool init();
        BV_CREATE_FUNC(MascotController);
    };
    
}


#endif /* MascotController_hpp */
