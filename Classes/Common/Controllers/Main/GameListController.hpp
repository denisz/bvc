//
//  GameListController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef GameListController_hpp
#define GameListController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class GameListController: public CollectionController {
    protected:
        void setupEndPoints();
        RequestCommand* commandForReloadData();
    public:
        BV_CREATE_FUNC(GameListController);
    };
}

#endif /* GameListController_hpp */
