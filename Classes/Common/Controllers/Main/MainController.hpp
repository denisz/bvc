//
//  MainController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef MainController_hpp
#define MainController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"
#include "MainViewController.hpp"
#include "PvPAvailableController.hpp"
#include "GameListController.hpp"
#include "PvPAvailableView.hpp"
#include "GameFlowController.hpp"
#include "AccountOnlineController.hpp"

namespace game {
    class MainController: public GameController {
    public:
        struct Options {};
        struct States  {};
    private:
        States _states;
        Options _options;
        void setup();
    protected:
        virtual UIKit::UIViewController* loadViewController();
        virtual bool init();
    public:
        BV_CREATE_FUNC(MainController);
    };
}

#endif /* MainController_hpp */
