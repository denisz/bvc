//
//  UINavigationController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "UINavigationController.hpp"
USING_NS_CC;

using namespace UIKit;

UINavigationControllerTransitionManager::UINavigationControllerTransitionManager() {
    
}

bool UINavigationControllerTransitionManager::init() {
    return true;
}

void UINavigationControllerTransitionManager::animateTransition(UIViewControllerContextTransitioning* transitionContext) {
    
    auto toView = transitionContext->viewForKey(UIViewControllerContextTransitioning::Keys::To);
    auto fromView = transitionContext->viewForKey(UIViewControllerContextTransitioning::Keys::From);
    auto _duration = this->transitionDuration(transitionContext);
    
    if (toView == nullptr) {
        animationEnded();
        return;
    }

    toView->setCascadeOpacityEnabled(true);
    
    if (presenting) {
        toView->setOpacity(0);
        
        cocos2d::ActionInterval* seq = (cocos2d::ActionInterval *)cocos2d::Sequence::create
        (
         FadeIn::create(_duration),
         CallFunc::create(CC_CALLBACK_0(UINavigationControllerTransitionManager::animationEndedWithContext, this, transitionContext)),
         nullptr
         );
        
        if (fromView != nullptr) {
            cocos2d::ActionInterval* seqFrom = (cocos2d::ActionInterval *)cocos2d::Sequence::create
            (
             FadeOut::create(_duration),
             Hide::create(),
             nullptr
             );

            fromView->runAction(seqFrom);
        }
        
        
        toView->runAction(seq);
    } else {
        cocos2d::ActionInterval* seq = (cocos2d::ActionInterval *)cocos2d::Sequence::create
        (
         FadeOut::create(_duration),
         CallFunc::create(CC_CALLBACK_0(UINavigationControllerTransitionManager::animationEndedWithContext, this, transitionContext)),
         nullptr
         );
        
//        if (fromView != nullptr) {
//            cocos2d::ActionInterval* seqFrom = (cocos2d::ActionInterval *)cocos2d::Sequence::create
//            (
//             FadeIn::create(_duration),
//             nullptr
//             );
//            
//            fromView->runAction(seqFrom);
//        }
        
        toView->runAction(seq);
    }
}

time_t UINavigationControllerTransitionManager::transitionDuration(UIViewControllerContextTransitioning* transitionContext) {
    return 1.0;
}

UINavigationController::UINavigationController()
: delegate(nullptr)
, topViewController(nullptr)
, visibleViewController(nullptr)
, _transitioningNavigationDelegate(nullptr)
, _navigationContainerView(nullptr) {

}

UINavigationController::~UINavigationController() {
    delegate = nullptr;
    clear();
    CC_SAFE_RELEASE_NULL(_navigationContainerView);
    CC_SAFE_RELEASE_NULL(_transitioningNavigationDelegate);
}

void UINavigationController::clear() {
    for (auto &item: _stackControllers) {
        CC_SAFE_RELEASE(item);
    }
    _stackControllers.clear();
}
bool UINavigationController::init() {
    _stackControllers = std::forward_list<UIViewController*>();
    
    auto transition = loadNavigationTransition();
    setNavigationTransition(transition);
    
    return UIViewController::init();
}

bool UINavigationController::initWithRootViewContorller(UIViewController* viewController) {
    auto result = UINavigationController::init();
    pushViewController(viewController, false);
    return result;
}

UINavigationController* UINavigationController::create() {
    auto ref = new UINavigationController();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

UINavigationController* UINavigationController::createWithRootViewController(UIViewController* viewController) {
    auto ref = new UINavigationController();
    if (ref->initWithRootViewContorller(viewController)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

void UINavigationController::didSetView(UIView* view) {
    if (_navigationContainerView != nullptr) {
        CC_SAFE_RELEASE_NULL(_navigationContainerView);
    }
    
    _navigationContainerView = UIView::create();
    view->addChild(_navigationContainerView, 1);    
}

std::forward_list<UIViewController*> UINavigationController::viewControllers() {
    return _stackControllers;
}

UIViewControllerTransitioningDelegate* UINavigationController::loadNavigationTransition() {
    return UINavigationControllerTransitionManager::create();
}

void UINavigationController::setNavigationTransition(UIViewControllerTransitioningDelegate* transitioningDelegate) {
    if (_transitioningNavigationDelegate != nullptr) {
        CC_SAFE_RELEASE_NULL(_transitioningNavigationDelegate);
    }
    
    _transitioningNavigationDelegate = transitioningDelegate;
}


UIView* UINavigationController::containerView() {
    return _navigationContainerView;
}

UIViewController* UINavigationController::determinePresentingViewController() {
    return this->visibleViewController;
}

bool UINavigationController::isExistsViewController(UIViewController* viewController) {
    auto it = std::find(_stackControllers.begin(), _stackControllers.end(), viewController);
    return it != _stackControllers.end();
}

UIViewController::Completion* UINavigationController::pushViewController(UIViewController* viewController, bool animated) {
    if (isExistsViewController(viewController)) {
        throw Error("The `ViewController` has already been added to this navigation controller");
    }

    auto presented  = viewController;
    auto source     = this;
    auto presenting = this->visibleViewController;
    
    auto context    = new UIViewControllerContextTransitioning();
    auto task       = context->task();
    CC_SAFE_AUTORELEASE(context);
    
    context->setFromViewController(presenting);
    context->setToViewController(presented);
    
    this->showViewController(viewController);
    this->visibleViewController = presented;
    
    if (_stackControllers.empty()) {
        topViewController = presented;
    }

    _stackControllers.push_front(viewController);
    CC_SAFE_RETAIN(viewController);
    
    if (_transitioningNavigationDelegate != nullptr && animated == true) {
        auto animator   = _transitioningNavigationDelegate->animationControllerForPresentedController(presented, presenting, source);
        
        animator->setContext(context);
        animator->animateTransition(context);
    } else {
        context->completeTransitionAsync();
    }
    
    return task;
}

UIViewController::Completion* UINavigationController::popViewControllerAnimated(bool animated) {
    if (_stackControllers.empty())
        return nullptr;
    
    auto viewController = _stackControllers.front();
    auto presented      = viewController;
    auto presenting     = viewController->presentingViewController();
    auto context        = new UIViewControllerContextTransitioning();
    auto task           = context->task();
    CC_SAFE_AUTORELEASE(context);

    context->setFromViewController(presenting);
    context->setToViewController(presented);
    
    this->visibleViewController = presenting;
    
    _stackControllers.pop_front();
    CC_SAFE_RELEASE(viewController);
    
    if (_stackControllers.empty()) {
        topViewController = nullptr;
    }

    if (_transitioningNavigationDelegate != nullptr && animated == true) {
        auto animator   = _transitioningNavigationDelegate->animationControllerForDismissedController(presented);
        
        animator->setContext(context);
        animator->animateTransition(context);
    } else {
        viewController->removeFromParent();
        context->completeTransitionAsync();
    }

    return task;
}

UIViewController::Completion* UINavigationController::popViewController(UIViewController* viewController, bool animated) {
    if (visibleViewController == viewController) {
        return popViewControllerAnimated(animated);
    }

    auto presented      = viewController;
    auto presenting     = viewController->presentingViewController();
    auto context        = new UIViewControllerContextTransitioning();
    auto task           = context->task();
    CC_SAFE_AUTORELEASE(context);
    
    context->setFromViewController(presenting);
    context->setToViewController(presented);
    
    this->visibleViewController = presenting;
    
    _stackControllers.remove(viewController);
    CC_SAFE_RELEASE(viewController);
    
    if (_stackControllers.empty()) {
        topViewController = nullptr;
    }
    
    if (_transitioningNavigationDelegate != nullptr && animated == true) {
        auto animator   = _transitioningNavigationDelegate->animationControllerForDismissedController(presented);
        
        animator->setContext(context);
        animator->animateTransition(context);
    } else {
        viewController->removeFromParent();
        context->completeTransitionAsync();
    }
    
    return task;
    
}