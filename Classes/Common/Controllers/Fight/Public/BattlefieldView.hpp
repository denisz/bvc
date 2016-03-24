//
//  BattlefieldView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef BattlefieldView_hpp
#define BattlefieldView_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "GridBase.hpp"

namespace game {
    class BattlefieldView: public UIKit::UIView {
    private:
        Geometry::GridBase* _gridBase;
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC_WITH_SIZE(BattlefieldView);
    };
}


#endif /* BattlefieldView_hpp */
