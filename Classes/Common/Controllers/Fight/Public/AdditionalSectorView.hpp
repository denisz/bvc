//
//  AdditionalSectorView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef AdditionalSectorView_hpp
#define AdditionalSectorView_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "GridBase.hpp"


namespace game {
    class AdditionalSectorView: public UIKit::UIView {
    private:
        Geometry::GridBase* _gridBase;
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC_WITH_SIZE(AdditionalSectorView);
    };
}

#endif /* AdditionalSectorView_hpp */
