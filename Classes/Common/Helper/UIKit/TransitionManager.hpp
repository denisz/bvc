//
//  TransitionManager.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef TransitionManager_hpp
#define TransitionManager_hpp

#include "stdafx.h"
#include "UIViewController.hpp"

//стандартный переход между viewcontroller
namespace game {
    class TransitionManager: public UIViewControllerAnimatedTransitioning, public UIViewControllerTransitioningDelegate  {
    private:
        bool presenting;
        TransitionManager();
        virtual bool init();
    public:
        
        // MARK: методы протокола UIViewControllerAnimatedTransitioning
        
        // метод, в котором непосредственно указывается анимация перехода от одного  viewcontroller к другому
        void animateTransition(UIViewControllerContextTransitioning* transitionContext);
        
        // метод возвращает количество секунд, которые длится анимация
        time_t transitionDuration(UIViewControllerContextTransitioning* transitionContext);
        
        // MARK: методы протокола UIViewControllerTransitioningDelegate
        
        // аниматор для презентации viewcontroller
        UIViewControllerAnimatedTransitioning* animationControllerForPresentedController(UIViewController* presented, UIViewController* presentingController, UIViewController* sourceController) {
            presenting = true;
            return this;
        }
        
        // аниматор для скрытия viewcontroller
        UIViewControllerAnimatedTransitioning* animationControllerForDismissedController(UIViewController* dismissed) {
            presenting = false;
            return this;
        }
        
        BV_CREATE_FUNC(TransitionManager);
    };
}

#endif /* TransitionManager_hpp */
