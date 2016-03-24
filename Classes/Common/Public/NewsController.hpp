//
//  NewsController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/23/16.
//
//

#ifndef NewsController_hpp
#define NewsController_hpp

#include "stdafx.h"
#include "CollectionController.hpp"

namespace game {
    class NewsController: public CollectionController {
    protected:
        virtual void setupEndPoints();
    public:
        BV_CREATE_FUNC(NewsController);
    };
}

#endif /* NewsController_hpp */
