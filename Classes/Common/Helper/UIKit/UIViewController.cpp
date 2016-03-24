//
//  UIViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "UIViewController.hpp"

using namespace UIKit;

UIViewControllerTransitionManager::UIViewControllerTransitionManager() {
    
}

bool UIViewControllerTransitionManager::init() {
    return true;
}

void UIViewControllerTransitionManager::animateTransition(UIViewControllerContextTransitioning* transitionContext) {
    animationEnded();
}

time_t UIViewControllerTransitionManager::transitionDuration(UIViewControllerContextTransitioning* transitionContext) {
    return 0.0;
}

UIViewControllerContextTransitioning::UIViewControllerContextTransitioning()
: _promise(nullptr)
, _from(nullptr)
, _to(nullptr){}

UIViewControllerContextTransitioning::~UIViewControllerContextTransitioning() {
    CC_SAFE_RELEASE_NULL(_promise);
    CC_SAFE_RELEASE_NULL(_from);
    CC_SAFE_RELEASE_NULL(_to);
}

void UIViewControllerContextTransitioning::setFromViewController(UIViewController* from) {
    CC_SAFE_RETAIN(from);
    _from = from;
}

void UIViewControllerContextTransitioning::setToViewController(UIViewController* to) {
    CC_SAFE_RETAIN(to);
    _to = to;
}

void UIViewControllerContextTransitioning::setPromise(Promise* promise) {
    CC_SAFE_RETAIN(promise);
    _promise = promise;
}

UIViewControllerContextTransitioning::Promise* UIViewControllerContextTransitioning::promise() {
    return _promise;
}

void UIViewControllerContextTransitioning::completeTransition(bool didComplete) {
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (_completed == false) {
        auto promise = this->promise();
        auto result  = new Bolts::BFBool(didComplete);
        CC_SAFE_DEFRREDRELEASE(result);
        promise->trySetResult(*result);
        _completed = true;
    }
}



void UIViewControllerContextTransitioning::completeTransitionAsync(bool didComplete) {
    CC_SAFE_RETAIN(this);
    completeTransition(didComplete);
    
    std::thread([this](){
//        usleep(100);
        sleep(1);
        CC_SAFE_RELEASE(this);
    }).detach();
}

UIView* UIViewControllerContextTransitioning::viewForKey(Keys key) {
    auto controller = viewControllerForKey(key);
    
    if (controller != nullptr) {
        return controller->view();
    }
    
    return nullptr;
}

UIViewController* UIViewControllerContextTransitioning::viewControllerForKey(Keys key) {
    switch (key) {
        case UIViewControllerContextTransitioning::Keys::From:
            if (_from != nullptr) {
                return _from;
            }
            break;
        case UIViewControllerContextTransitioning::Keys::To:
            if (_to != nullptr) {
                return _to;
            }
            
            break;
    }
    
    return nullptr;
}

bool UIViewControllerContextTransitioning::isCompleted() {
    return _completed;
}

UIViewController::UIViewController()
: _view(nullptr)
, _transitioningDelegate(nullptr) {
    _childControllers = std::vector<UIViewController*>();
}

UIViewController::~UIViewController() {
    _view->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(_view);
    CC_SAFE_RELEASE_NULL(_transitioningDelegate);
    std::cout << "Destroy UIViewController" << std::endl;
}

UIViewController* UIViewController::create() {
    auto ref = new UIViewController();
    
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

UIViewController* UIViewController::createWithSize(const cocos2d::Size &contentSize) {
    auto ref = new UIViewController();
    
    if (ref->initWithSize(contentSize)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool UIViewController::init() {
    auto view = loadView();
    setView(view);
    
    auto transition = loadTransition();
    setTransition(transition);

    return true;
}

bool UIViewController::initWithSize(const cocos2d::Size &contentSize) {
    if (init()) {
        view()->setContentSize(contentSize);
        return true;
    }
    
    return false;
}

UIView* UIViewController::loadView() {
    return UIView::create();
}

UIViewControllerTransitioningDelegate* UIViewController::loadTransition() {
    return UIViewControllerTransitionManager::create();
}

void UIViewController::setView(UIView* view) {
    if (_view != nullptr) {
        CC_SAFE_RELEASE_NULL(_view);
    }
    
    view->setContentSize(preferredContentSize());
    willSetView(view);
    _view = view;
    didSetView(view);
    viewDidLoad();
}

UIView* UIViewController::view() {
    return _view;
}

UIView* UIViewController::containerView() {
    return _view;
}

void UIViewController::setTransition(UIViewControllerTransitioningDelegate* transitioningDelegate) {
    if (_transitioningDelegate != nullptr) {
        CC_SAFE_RELEASE_NULL(_transitioningDelegate);
    }
    
    _transitioningDelegate = transitioningDelegate;
}

/**
 ->continueWithBlock([this](UIViewController::Completion *task) -> UIViewController::Completion* {
 return nullptr;
 })*/

UIViewController::Completion* UIViewController::presentViewController(UIViewController* viewController, bool animated) {
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    CC_SAFE_DEFRREDRELEASE(promise);
    
    auto task       = promise->task();
    auto presented  = viewController;
    auto presenting = this;
    auto source     = this;

    auto context = new UIViewControllerContextTransitioning();
    CC_SAFE_AUTORELEASE(context);
    
    context->setFromViewController(presenting);
    context->setToViewController(presented);
    context->setPromise(promise);
    
    this->showViewController(viewController);
    
    if (_transitioningDelegate != nullptr && animated == true) {
        auto animator   = _transitioningDelegate->animationControllerForPresentedController(presented, presenting, source);
        
        animator->setContext(context);
        animator->animateTransition(context);
    } else {
        context->completeTransitionAsync();
    }
    
    return task;
}

UIViewController::Completion* UIViewController::dismissViewControllerAnimated(bool animated) {
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    CC_SAFE_DEFRREDRELEASE(promise);
    
    auto task       = promise->task();
    auto presented  = this;
    auto presenting = this->_presentingViewController;
    
    auto context    = new UIViewControllerContextTransitioning();
    CC_SAFE_AUTORELEASE(context);
    
    context->setFromViewController(presenting);
    context->setToViewController(presented);
    context->setPromise(promise);
    
    if (_transitioningDelegate != nullptr && animated == true) {
        auto animator   = _transitioningDelegate->animationControllerForDismissedController(this);
        
        animator->setContext(context);
        animator->animateTransition(context);
        
        return task->continueWithBlock([this](UIViewController::Completion *task) -> UIViewController::Completion* {
            this->removeFromParent();
            return nullptr;
        });
    } else {
        this->removeFromParent();
        context->completeTransitionAsync();
    }
    
    return task;
}

void UIViewController::showViewController(UIViewController* viewController) {
    auto parentContainerView    = this->containerView();
    auto childView              = viewController->view();
    
    viewController->willMoveToParentViewController(this);
    viewController->viewWillAppear();
    childView->setPosition(cocos2d::Vec2::ZERO);
    childView->setContentSize(frameForContentController());
    parentContainerView->addChild(childView, 1);
    viewController->_presentingViewController = determinePresentingViewController();
    viewController->viewDidAppear();
    viewController->didMoveToParentViewController(this);
}

UIViewController* UIViewController::determinePresentingViewController() {
    return this;
}

void UIViewController::viewDidLoad()      {};
void UIViewController::viewWillAppear()   {};
void UIViewController::viewDidAppear()    {};
void UIViewController::viewWillDisappear(){};
void UIViewController::viewDidDisappear() {};

UIViewController* UIViewController::presentingViewController() {
    return _presentingViewController;
}

void UIViewController::childViewControllers(UIViewController& viewController) {
}

void UIViewController::removeFromParentViewController(UIViewController& viewController) {
}

void UIViewController::willMoveToParentViewController(UIViewController* viewController) {
}

void UIViewController::didMoveToParentViewController(UIViewController* viewController) {
    this->_parentViewController = viewController;
}

void UIViewController::removeFromParent() {
    this->viewWillDisappear();
    this->_presentingViewController = nullptr;
    this->_parentViewController = nullptr;
    this->view()->removeFromParentAndCleanup(true);
    this->viewDidDisappear();
}

cocos2d::Size UIViewController::preferredContentSize() {
    auto director = cocos2d::Director::getInstance();
    return director->getVisibleSize();
}

cocos2d::Size UIViewController::frameForContentController() {
    return preferredContentSize();
}

