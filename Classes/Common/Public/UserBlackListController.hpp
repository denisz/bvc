//
//  UserBlackListController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef UserBlackListController_hpp
#define UserBlackListController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class UserBlackListController: public CollectionController {
    protected:
        virtual void setupEndPoints();
        virtual RequestCommand* commandForReloadData();
    public:
        BV_CREATE_FUNC(UserBlackListController);
    };
}


#endif /* UserBlackListController_hpp */
