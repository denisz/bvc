//
//  UINavigationController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef UINavigationController_hpp
#define UINavigationController_hpp

#include "stdafx.h"
#include "UIViewController.hpp"


namespace game {
    class UINavigationController: public UIViewController {
    public:
        enum class Operation {NONE, PUSH, POP};
        class Delegate {
            virtual void willShowViewController(UIViewController* viewController, bool animated) {};
            virtual void didShowViewController(UIViewController* viewController, bool animated) {};
        };
    private:
        std::vector<UIViewController*> _stackControllers;
    protected:
        UINavigationController();
        bool init();
        bool initWithRootViewContorller(UIViewController* viewController);
    public:
        UIViewController* topViewController;
        UIViewController* visibleViewController;
        std::vector<UIViewController*> viewControllers();
        
        ~UINavigationController();
        Delegate* delegate;
        void showViewController(UIViewController* viewController);
        void pushViewController(UIViewController* viewController, bool animated);
        UIViewController* popViewControllerAnimated(bool animated);
        std::vector<UIViewController*> popToRootViewControllerAnimated(bool animated);
        std::vector<UIViewController*> popToViewController(UIViewController* viewController, bool animated);
        
        UINavigationController* create();
        UINavigationController* createWithRootViewController(UIViewController* viewController);
    };
}

#endif /* UINavigationController_hpp */
