//
//  RootController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/1/16.
//
//

#ifndef RootController_hpp
#define RootController_hpp

#include "stdafx.h"
#include "GameController.hpp"
#include "RootViewController.hpp"

namespace game {
    class RootController: public GameController {
    private:
        static RootController* _instance;
    protected:
        RootController();
        virtual UIKit::UIViewController* loadViewController();
    public:
        virtual bool init();
        void presentController(GameController* controller, bool animated = true);
        void dismissController(GameController* controller, bool animated = true);
        void dismissController(bool animated = true);
        static RootController* getInstance();
        BV_CREATE_FUNC(RootController);
    };
}

#endif /* RootController_hpp */
