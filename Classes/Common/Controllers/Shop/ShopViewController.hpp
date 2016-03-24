//
//  ShopViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef ShopViewController_hpp
#define ShopViewController_hpp

#include "stdafx.h"
#include "GameViewController.hpp"
#include "ServiceLocator.hpp"
#include "User.hpp"

namespace game {
    class ShopViewController: public GameViewController {
    public:
        BV_CREATE_FUNC(ShopViewController);
    };
}

#endif /* ShopViewController_hpp */
