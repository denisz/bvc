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
        virtual void loadViewController();
    public:
        virtual bool init();
        void setTop(GameController* controller, bool animated = true);
        void push_front(GameController* controller, bool animated = true);
        void pop_front(bool animated = true);
        static RootController* getInstance();
        BV_CREATE_FUNC(RootController);
    };
}

#endif /* RootController_hpp */
