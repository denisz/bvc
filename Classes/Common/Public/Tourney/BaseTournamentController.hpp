//
//  BaseTournamentController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef BaseTournamentController_hpp
#define BaseTournamentController_hpp

#include "stdafx.h"
#include "GameViewController.hpp"


namespace game {
    class BaseTournamentController: public GameViewController {
    public:
        virtual bool init();
    };
}


#endif /* BaseTournamentController_hpp */
