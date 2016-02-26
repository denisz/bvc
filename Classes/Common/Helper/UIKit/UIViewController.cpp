//
//  UIViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "UIViewController.hpp"

using namespace game;

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
    _from = from;
    CC_SAFE_RETAIN(_from);
}

void UIViewControllerContextTransitioning::setToViewController(UIViewController* to) {
    _to = to;
    CC_SAFE_RETAIN(_to);
}

void UIViewControllerContextTransitioning::setPromise(Promise* promise) {
    _promise = promise;
    CC_SAFE_RETAIN(promise);
}

game::UIViewControllerContextTransitioning::Promise* UIViewControllerContextTransitioning::promise() {
    return _promise;
}

void UIViewControllerContextTransitioning::completeTransition(bool didComplete) {
    auto promise = this->promise();
    auto result  = new Bolts::BFBool(didComplete);
    _completed = true;
    promise->trySetResult(*result);
}

UIView* UIViewControllerContextTransitioning::viewForKey(Keys& key) {
    auto controller = viewControllerForKey(key);
    
    if (controller != nullptr) {
        return controller->view();
    }
    
    return nullptr;
}

UIViewController* UIViewControllerContextTransitioning::viewControllerForKey(Keys& key) {
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
    CC_SAFE_RELEASE_NULL(_view);
    CC_SAFE_RELEASE_NULL(_transitioningDelegate);
}

UIViewController* UIViewController::create() {
    auto ref = new UIViewController();
    
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool UIViewController::init() {
    auto view = loadView();
    setView(view);
    return true;
}

UIView* UIViewController::loadView() {
    return UIView::create();
}

void UIViewController::setView(UIView* view) {
    if (_view != nullptr) {
        CC_SAFE_RELEASE_NULL(_view);
    }
    
    _view = view;
    viewDidLoad();
}

UIView* UIViewController::view() {
    return _view;
}

void UIViewController::setTransition(UIViewControllerTransitioningDelegate* transitioningDelegate) {
    if (_transitioningDelegate != nullptr) {
        CC_SAFE_RELEASE_NULL(_transitioningDelegate);
    }
    
    _transitioningDelegate = transitioningDelegate;
    CC_SAFE_RETAIN(transitioningDelegate);
}

UIViewController::Completion* UIViewController::presentViewController(UIViewController* viewController, bool animated) {
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    auto task = promise->task();
    
    if (_transitioningDelegate != nullptr) {
        auto presented  = viewController;
        auto presenting = this;
        auto source     = this;
        
        auto animator = _transitioningDelegate->animationControllerForPresentedController(presented, presenting, source);
        
        auto context = new UIViewControllerContextTransitioning();
        context->setFromViewController(presenting);
        context->setToViewController(presented);
        context->setPromise(promise);
        
        viewController->viewWillAppear();
        
        try{
            animator->animateTransition(context);
            viewController->viewDidAppear();
        } catch(std::exception* e) {}

        viewController->_presentingViewController = this;
        viewController->willMoveToParentViewController(this);

        return task->continueWithBlock([&](UIViewController::Completion *task) -> UIViewController::Completion* {
            viewController->didMoveToParentViewController(this);
            CC_SAFE_RELEASE(context);
            return nullptr;
        });
    } else {
        
    }
    
    return task;
}

UIViewController::Completion* UIViewController::dismissViewControllerAnimated(bool animated) {
    auto promise = UIViewControllerContextTransitioning::Promise::taskCompletionSource();
    auto task = promise->task();
    
    if (_transitioningDelegate != nullptr) {
        auto presented  = this;
        auto presenting = this->_presentingViewController;

        auto animator = _transitioningDelegate->animationControllerForDismissedController(this);
        auto context = new UIViewControllerContextTransitioning();
        context->setFromViewController(presenting);
        context->setToViewController(presented);
        context->setPromise(promise);

        this->viewWillDisappear();
        
        try{
            animator->animateTransition(context);
            this->viewDidDisappear();
        } catch(std::exception* e) {}
        
        this->_presentingViewController = nullptr;
        this->_parentViewController = nullptr;
        
        return task->continueWithBlock([&](UIViewController::Completion *task) -> UIViewController::Completion* {
            CC_SAFE_RELEASE(context);
            return nullptr;
        });
    } else {
    
    }
    
    return task;
}

void UIViewController::showViewController(UIViewController* viewController) {
    auto parentView = this->view();
    auto childView = viewController->view();
    viewController->viewWillDisappear();
    parentView->addChild(childView);
    viewController->viewDidDisappear();
    
    viewController->didMoveToParentViewController(this);
}

void UIViewController::viewDidLoad()      {};
void UIViewController::viewWillAppear()   {};
void UIViewController::viewDidAppear()    {};
void UIViewController::viewWillDisappear(){};
void UIViewController::viewDidDisappear() {};

void UIViewController::childViewControllers(UIViewController& viewController) {
}

void UIViewController::removeFromParentViewController(UIViewController& viewController) {
}

void UIViewController::willMoveToParentViewController(UIViewController* viewController) {
}

void UIViewController::didMoveToParentViewController(UIViewController* viewController) {
    this->_parentViewController = viewController;
}

