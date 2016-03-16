//
//  UserFriendsController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef UserFriendsController_hpp
#define UserFriendsController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class UserFriendsController: public CollectionController {
    protected:
        virtual void setupEndPoints();
        virtual RequestCommand* commandForReloadData();
    public:
        BV_CREATE_FUNC(UserFriendsController);
    };
}


#endif /* UserFriendsController_hpp */
