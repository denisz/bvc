//
//  AccountOnlineController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef AccountOnlineController_hpp
#define AccountOnlineController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"
#include "User.hpp"

namespace game {
    class AccountOnlineController: public CollectionController {
    protected:
        virtual void setupEndPoints();
        virtual RequestCommand* commandForReloadData();
    public:
        bool isOnlineAccount(User& user);
        bool isOnlineAccountById(const std::string &objectId);
        bool isOnlineAccountById(int objectId);
        BV_CREATE_FUNC(AccountOnlineController);
    };
}

#endif /* AccountOnlineController_hpp */
