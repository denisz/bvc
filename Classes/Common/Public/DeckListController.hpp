//
//  DeckListController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#ifndef DeckListController_hpp
#define DeckListController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class DeckListController: public CollectionController {
    protected:
        void setupEndPoints();
        RequestCommand* commandForReloadData();
    public:
        BV_CREATE_FUNC(DeckListController);
    };
}

#endif /* DeckListController_hpp */
