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
    if (toView == nullptr) {
        animationEnded();
        return;
    }
    
    auto _duration = this->transitionDuration(transitionContext);

    toView->setCascadeOpacityEnabled(true);
    toView->setOpacity(0);
    
    cocos2d::ActionInterval* a = (cocos2d::ActionInterval *)cocos2d::Sequence::create
    (
     FadeIn::create(_duration),
     CallFunc::create(CC_CALLBACK_0(UINavigationControllerTransitionManager::animationEnded, this)),
     nullptr
     );

     toView->runAction(a);
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
    _stackControllers.clear();
    CC_SAFE_RELEASE_NULL(_navigationContainerView);
    CC_SAFE_RELEASE_NULL(_transitioningNavigationDelegate);
}

bool UINavigationController::init() {
    _stackControllers = std::forward_list<UIViewController*>();
    
    auto transition = loadNavigationTransition();
    setNavigationTransition(transition);
    
    return UIViewController::init();
}

bool UINavigationController::initWithRootViewContorller(UIViewController* viewController) {
    auto result = UINavigationController::init();
    setTopViewControllerAnimated(viewController, false);
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

void UINavigationController::setView(UIView* view) {
    if (_navigationContainerView != nullptr) {
        CC_SAFE_RELEASE_NULL(_navigationContainerView);
    }
    
    _navigationContainerView = UIView::create();
    view->addChild(_navigationContainerView, 1);
    
    UIViewController::setView(view);
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

UIViewController::Completion* UINavigationController::pushViewController(UIViewController* viewController, bool animated) {
    auto it = std::find(_stackControllers.begin(), _stackControllers.end(), viewController);
    if (it != _stackControllers.end()) {
        throw Error("The `ViewController` has already been added to this navigation controller");
    }
    
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    auto task = promise->task();
    
    _stackControllers.push_front(viewController);
    
    if (_transitioningNavigationDelegate != nullptr && animated == true) {
        auto presented  = viewController;
        auto presenting = this->visibleViewController;
        auto source     = this;
        auto animator   = _transitioningNavigationDelegate->animationControllerForPresentedController(presented, presenting, source);
        
        auto context = new UIViewControllerContextTransitioning();
        CC_SAFE_AUTORELEASE(context);
        
        context->setFromViewController(presenting);
        context->setToViewController(presented);
        context->setPromise(promise);
        
        showViewController(viewController);
        this->visibleViewController = viewController;
        
        animator->setContext(context);
        animator->animateTransition(context);
        
        return task->continueWithBlock([this](UIViewController::Completion *task) -> UIViewController::Completion* {
            return nullptr;
        });
    } else {
        this->visibleViewController = viewController;
        showViewController(viewController);
        auto result = new Bolts::BFBool(true);
        promise->trySetResult(*result);
    }
    
    return task;
}

UIViewController* UINavigationController::popViewControllerAnimated(bool animated) {
    auto viewController = _stackControllers.front();
    
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    auto task = promise->task();
    
    if (_transitioningNavigationDelegate != nullptr && animated == true) {
        auto presented  = viewController;
        auto presenting = viewController->presentingViewController();
        auto animator   = _transitioningNavigationDelegate->animationControllerForDismissedController(this);
        auto context    = new UIViewControllerContextTransitioning();
        CC_SAFE_AUTORELEASE(context);
        
        context->setFromViewController(presenting);
        context->setToViewController(presented);
        context->setPromise(promise);
        
        this->viewWillDisappear();
        
        this->visibleViewController = presenting;
        
        animator->setContext(context);
        animator->animateTransition(context);
        
        task->continueWithBlock([&](UIViewController::Completion *task) -> UIViewController::Completion* {
            CC_SAFE_RELEASE(context);
            viewController->removeFromParent();
            return nullptr;
        });
    } else {
        this->viewWillDisappear();
        this->_presentingViewController = nullptr;
        this->_parentViewController = nullptr;
        auto view = this->view();
        view->removeFromParent();
        this->viewDidDisappear();
    }
    
    _stackControllers.pop_front();
    return viewController;
}

std::vector<UIViewController*> UINavigationController::popToRootViewControllerAnimated(bool animated) {
    auto stack = std::vector<UIViewController*>();
    
    return stack;
}

UIViewController::Completion* UINavigationController::setTopViewControllerAnimated(UIViewController* viewController,bool animated) {
    
    return pushViewController(viewController, animated)->continueWithBlock([&](UIViewController::Completion *task) -> UIViewController::Completion* {
        _stackControllers.clear();
        _stackControllers.push_front(viewController);
        this->topViewController = viewController;
        return nullptr;
    });
}