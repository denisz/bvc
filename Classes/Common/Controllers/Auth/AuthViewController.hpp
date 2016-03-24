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
#include "GameViewController.hpp"

namespace game {
    class AuthViewController: public GameViewController {
    private:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(AuthViewController);
    };
}


#endif /* AuthViewController_hpp */
