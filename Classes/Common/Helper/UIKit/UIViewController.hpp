//
//  UIViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef UIViewController_hpp
#define UIViewController_hpp

#include "stdafx.h"
#include "UIView.hpp"
#include "UIViewContorollerType.h"

namespace UIKit {
    class UIViewControllerContextTransitioning: public internal::AIRef {
    public:
        typedef Bolts::BFTaskCompletionSource<Bolts::BFBool> Promise;
    private:
        UIViewController*   _from;
        UIViewController*   _to;
        Promise*            _promise;
        bool                _completed;
        std::mutex          _mutex;
    public:
        UIViewControllerContextTransitioning();
        ~UIViewControllerContextTransitioning();
        enum class Keys{From, To};
        void setPromise(Promise* promise);
        void setFromViewController(UIViewController* from);
        void setToViewController(UIViewController* to);
        bool isCompleted();
        
        void completeTransition(bool didComplete = true);
        void completeTransitionAsync(bool didComplete = true);
        Promise* promise();
        
        UIView* viewForKey(Keys key);
        UIViewController* viewControllerForKey(Keys key);
        
        public:
        
    };
    
    class UIViewControllerAnimatedTransitioning {
    private:
        UIViewControllerContextTransitioning* _context;
    protected:
        void animationEnded() {
            return animationEndedWithContext(_context);
        }
        
        void animationEndedWithContext(UIViewControllerContextTransitioning* context) {
            if (_context == context) {
                _context->completeTransition(true);
                CC_SAFE_RELEASE_NULL(_context);
            }
        };
    public:
        void setContext(UIViewControllerContextTransitioning* context) {
            if (_context != nullptr) {
                animationEndedWithContext(_context);
            }
            
            CC_SAFE_RETAIN(context);
            _context = context;
        }
        virtual void animateTransition(UIViewControllerContextTransitioning* transitionContext) = 0;
        virtual time_t transitionDuration(UIViewControllerContextTransitioning* transitionContext) = 0;
    };

    /**
    presented:
     The view controller object that is about to be presented onscreen.
    presenting:
     The view controller that is presenting the view controller in the presented parameter. The object in this parameter could be the root view controller of the window, a parent view controller that is marked as defining the current context, or the last view controller that was presented. This view controller may or may not be the same as the one in the source parameter.
    source:
     The view controller whose presentViewController:animated:completion: method was called.
    **/
    
    class UIViewControllerTransitioningDelegate: public internal::AIRef {
    public:
        virtual UIViewControllerAnimatedTransitioning* animationControllerForPresentedController(UIViewController* presented, UIViewController* presentingController, UIViewController* sourceController) = 0;
        virtual UIViewControllerAnimatedTransitioning* animationControllerForDismissedController(UIViewController* dismissed) = 0;
    };
    
    class UIViewControllerTransitionManager: public UIViewControllerAnimatedTransitioning, public UIViewControllerTransitioningDelegate  {
    private:
        bool presenting;
        UIViewControllerTransitionManager();
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
        
        BV_CREATE_FUNC(UIViewControllerTransitionManager);
    };
    
    class UIViewController: public internal::AIRef {
    public:
        typedef Bolts::BFTask<Bolts::BFBool> Completion;
    private:
        UIView* _view;
        UIViewControllerTransitioningDelegate* _transitioningDelegate;
        std::vector<UIViewController*> _childControllers;
    protected:
        UIViewController();

        UIViewController* _presentingViewController;
        UIViewController* _presentedViewController;
        UIViewController* _parentViewController;

        virtual UIView* loadView();
        virtual UIViewControllerTransitioningDelegate* loadTransition();
        virtual UIViewController* determinePresentingViewController();
    public:
        virtual bool init();
        virtual bool initWithSize(const cocos2d::Size &contentSize);
        
        ~UIViewController();
        
        virtual cocos2d::Size preferredContentSize();
        virtual cocos2d::Size frameForContentController();
// MARK: life cycle
        virtual void viewDidLoad();
        virtual void viewWillAppear();
        virtual void viewDidAppear();
        virtual void viewWillDisappear();
        virtual void viewDidDisappear();
        
//MARK: constructor
        UIView* view();
        
        UIViewController* presentingViewController();
        
        void setView(UIView* view);
        void setTransition(UIViewControllerTransitioningDelegate* transitioningDelegate);
        
        virtual void willSetView(UIView* view) {};
        virtual void didSetView(UIView* view) {};
        virtual UIView* containerView();

        virtual Completion* presentViewController(UIViewController* viewController, bool animated);
        virtual Completion* dismissViewControllerAnimated(bool animated);
        virtual void showViewController(UIViewController* viewController);
        virtual void willMoveToParentViewController(UIViewController* viewController);
        virtual void didMoveToParentViewController(UIViewController* viewController);
        
        void removeFromParent();
        void childViewControllers(UIViewController& viewController);
        void removeFromParentViewController(UIViewController& viewController);
        
    public:
        static UIViewController* create();
        static UIViewController* createWithSize(const cocos2d::Size &contentSize);
    };
}
#endif /* UIViewController_hpp */
