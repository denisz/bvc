//
//  DraftTournamentController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef DraftTournamentController_hpp
#define DraftTournamentController_hpp


#include "stdafx.h"
#include "BaseTournamentController.hpp"

namespace game {
    class DraftTournamentController: public BaseTournamentController {
    public:
        BV_CREATE_FUNC(DraftTournamentController);
    };
}

#endif /* DraftTournamentController_hpp */
