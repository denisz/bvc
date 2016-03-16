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
#include "GCD.hpp"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

namespace UIKit {
    class UIView: public cocos2d::ui::Layout {
    protected:
        virtual void viewDidLoad();
    public:
        virtual bool init();
        virtual bool initWithSize(const cocos2d::Size &contentSize);
        
        BV_CREATE_FUNC(UIView)
        BV_CREATE_FUNC_WITH_SIZE(UIView);
    };
}

#endif /* UIView_hpp */
