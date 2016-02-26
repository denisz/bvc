//
//  UIWindow.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef UIWindow_hpp
#define UIWindow_hpp

#include "stdafx.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UIViewController.hpp"

namespace game {
    class UIWindow: public UIViewController {
        cocos2d::Scene* _scene;
        UIViewController* _rootViewController;
        void viewDidLoad();
    protected:
        UIWindow();
        virtual bool init();
    public:
        ~UIWindow();
        
        void setRootViewController(UIViewController* controller);
        cocos2d::Scene* scene();
        
        BV_CREATE_FUNC(UIWindow);
    };
}
#endif /* UIWindow_hpp */
