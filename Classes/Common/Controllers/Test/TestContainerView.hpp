//
//  TestContainerView.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#ifndef TestContainerView_hpp
#define TestContainerView_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "FightCardController.hpp"
#include "GridBase.hpp"

namespace game {
    class TestContainerView: public UIKit::UIView, public FCAT {
    private:
        Geometry::GridBase* _gridBase;
    private:
        cocos2d::Vec2 getCoordinateByXAndY(int x, int y);
        virtual void viewDidLoad();
        virtual void animateTransition(FightCardContextTransitioning* transitionContext);
    public:
        TestContainerView();
        ~TestContainerView();
        bool init();
        BV_CREATE_FUNC_WITH_SIZE(TestContainerView);
    };
}

#endif /* TestContainerView_hpp */
