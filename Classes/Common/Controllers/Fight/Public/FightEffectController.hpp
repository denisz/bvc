//
//  FightEffectController.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/5/16.
//
//

#ifndef FightEffectController_hpp
#define FightEffectController_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class FightEffectController: UIKit::UIView {
    public:
        bool init();
        BV_CREATE_FUNC(FightEffectController);
    };
}

#endif /* FightEffectController_hpp */
