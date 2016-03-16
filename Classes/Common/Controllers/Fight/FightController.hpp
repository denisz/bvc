//
//  FightController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#ifndef FightController_hpp
#define FightController_hpp

#include "stdafx.h"
#include "GameController.hpp"
#include "FightViewController.hpp"

using namespace internal::network;

namespace game {
    class FightController: public GameController {
    private:
        bool checkFightController(Response* res);
        
    protected:
        bool commandGameFinish(Response* res);
        bool commandGameEquipment(Response* res);
        bool commandGameChooseDeck(Response* res);
        bool commandGameSetup(Response* res);
        bool commandGameTimers(Response* res);
        bool commandGameCreateCards(Response* res);
        bool commandGameDeleteCards(Response* res);
        bool commandGameCreateAbl(Response* res);
        bool commandGameDeleteAbl(Response* res);
        bool commandGameLog(Response* res);
        bool commandGameUpdateCards(Response* res);
        bool commandGameDialog(Response* res);
        bool commandGameOfferDraw(Response* res);
        bool commandGameCancelDraw(Response* res);
        
        bool error(Response* res);
        
        virtual UIKit::UIViewController* loadViewController();
    public:
        void resume();
        virtual bool init();
        BV_CREATE_FUNC(FightController);
    };
}

#endif /* FightController_hpp */
