//
//  UIView.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef UIView_hpp
#define UIView_hpp

#include "stdafx.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace UIKit {
    class UIView: public cocos2d::ui::Layout {
    protected:
        virtual bool init();
    public:
        BV_CREATE_FUNC(UIView)
    };
}

#endif /* UIView_hpp */
