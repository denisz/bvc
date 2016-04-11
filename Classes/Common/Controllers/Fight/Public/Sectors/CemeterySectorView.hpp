//
//  CemeterySectorView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef CemeterySectorView_hpp
#define CemeterySectorView_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "FightCardController.hpp"

namespace game {
    class CemeterySectorView: public UIKit::UIView, public FigthCardAnimatedTransitioning {
    private:
        virtual void viewDidLoad();
        virtual void animateTransition(FightCardContextTransitioning* transitionContext);
    public:
        BV_CREATE_FUNC_WITH_SIZE(CemeterySectorView);
    };
}

#endif /* CemeterySectorView_hpp */
