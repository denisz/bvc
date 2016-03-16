//
//  AuthController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef AuthController_hpp
#define AuthController_hpp

#include "stdafx.h"
#include "GameController.hpp"
#include "AuthViewController.hpp"

namespace game {
    class AuthController: public GameController {
    private:
        void actionAuth();
        virtual UIKit::UIViewController* loadViewController();
        virtual void processOpen();
    public:
        virtual bool init();
        BV_CREATE_FUNC(AuthController);
    };
}

#endif /* AuthController_hpp */
