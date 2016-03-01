//
//  MainViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/7/16.
//
//

#ifndef MainViewController_hpp
#define MainViewController_hpp

#include "stdafx.h"
#include "UIViewController.hpp"
#include "ServiceLocator.hpp"

namespace game {
    class MainViewController: public UIKit::UIViewController {
    protected:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(MainViewController);
    };
}
#endif /* MainViewController_hpp */
