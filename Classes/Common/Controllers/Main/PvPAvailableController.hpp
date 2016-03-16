//
//  PvPAvailableController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef PvPAvailableController_hpp
#define PvPAvailableController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class PvPAvailableController: public CollectionController {
    protected:
        virtual void setupEndPoints();
        virtual RequestCommand* commandForReloadData();
    public:
        BV_CREATE_FUNC(PvPAvailableController);
    };
}

#endif /* PvPAvailableController_hpp */
