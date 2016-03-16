//
//  GameFlowController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef GameFlowController_hpp
#define GameFlowController_hpp

#include "stdafx.h"
#include "GameController.hpp"
#include "GameFlowViewController.hpp"

namespace game {
    class GameFlowController: public GameController {
    private:
        bool commandGameInit(internal::network::Response* res);
        bool commandTourneySigIn(internal::network::Response* res);
        virtual UIKit::UIViewController* loadViewController();
    public:
        GameFlowController();
        ~GameFlowController();
        virtual bool init();
        
        BV_CREATE_FUNC(GameFlowController);
    };
}

#endif /* GameFlowController_hpp */
