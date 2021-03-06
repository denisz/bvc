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


namespace UIKit {
    
    class UINavigationControllerTransitionManager: public UIViewControllerAnimatedTransitioning, public UIViewControllerTransitioningDelegate  {
    private:
        bool presenting;
        UINavigationControllerTransitionManager();
        virtual bool init();
    public:
        void animateTransition(UIViewControllerContextTransitioning* transitionContext);
        time_t transitionDuration(UIViewControllerContextTransitioning* transitionContext);
        
        UIViewControllerAnimatedTransitioning* animationControllerForPresentedController(UIViewController* presented, UIViewController* presentingController, UIViewController* sourceController) {
            presenting = true;
            return this;
        }
        UIViewControllerAnimatedTransitioning* animationControllerForDismissedController(UIViewController* dismissed) {
            presenting = false;
            return this;
        }
        BV_CREATE_FUNC(UINavigationControllerTransitionManager);
    };

    
    class UINavigationController: public UIViewController {
    public:
        class Delegate {
            virtual void willShowViewController(UIViewController* viewController, bool animated) {};
            virtual void didShowViewController(UIViewController* viewController, bool animated) {};
        };
    private:
        UIView* _navigationContainerView;
        std::forward_list<UIViewController*> _stackControllers;
        UIViewControllerTransitioningDelegate* _transitioningNavigationDelegate;
        virtual void didSetView(UIView* view);
        void setNavigationTransition(UIViewControllerTransitioningDelegate* transitioningDelegate);
        bool isExistsViewController(UIViewController* viewController);
        void clear();
    protected:
        UINavigationController();
        virtual bool init();
        virtual UIView* containerView();
        virtual UIViewController* determinePresentingViewController();
        UIViewControllerTransitioningDelegate* loadNavigationTransition();
        bool initWithRootViewContorller(UIViewController* viewController);
    public:
        UIViewController* topViewController;
        UIViewController* visibleViewController;
        std::forward_list<UIViewController*> viewControllers();
        
        ~UINavigationController();
        Delegate* delegate;
        UIViewController::Completion* pushViewController(UIViewController* viewController, bool animated = true);
        UIViewController::Completion* popViewController(UIViewController* viewController, bool animated = true);
        UIViewController::Completion* popViewControllerAnimated(bool animated = true);
        
        static UINavigationController* create();
        static UINavigationController* createWithRootViewController(UIViewController* viewController);
    };
}

#endif /* UINavigationController_hpp */
