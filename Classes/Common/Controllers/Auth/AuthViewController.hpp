//
//  AuthViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef AuthViewController_hpp
#define AuthViewController_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class AuthViewController: public UIKit::UIViewController {
    private:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(AuthViewController);
    };
}


#endif /* AuthViewController_hpp */
