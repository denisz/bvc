//
//  RootViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/1/16.
//
//

#ifndef RootViewController_hpp
#define RootViewController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"

namespace game {
    class RootViewController: public GameViewController {
    private:
        static RootViewController* _instance;
        UIKit::UINavigationController* _navigationController;
        virtual void viewDidLoad();
        BV_CREATE_FUNC(RootViewController);
    public:
        RootViewController();
        ~RootViewController();
        
        void pushViewController(UIKit::UIViewController* viewController, bool animated = true);
        void popViewControllerAnimated(bool animated = true);
        
        static RootViewController* sharedInstance();
    };
}

#endif /* RootViewController_hpp */
