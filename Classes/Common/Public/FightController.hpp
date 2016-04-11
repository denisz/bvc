//
//  FightController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/21/16.
//
//

#ifndef FightController_hpp
#define FightController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class FightController: public internal::AIRef, public ICommandController {
    public:
        CommandRunner::Handler* pass(int gameId);
        CommandRunner::Handler* deal(int gameId);
        CommandRunner::Handler* draw(int gameId);
        CommandRunner::Handler* surrender(int gameId);
        CommandRunner::Handler* saveReplay(int gameId);
        CommandRunner::Handler* chooseDeck(int gameId,  const int deckId);
        CommandRunner::Handler* selection(int gameId,   const BVValueVector& selection);
        CommandRunner::Handler* ability(int gameId,     const internal::BVValueMap& data);
        CommandRunner::Handler* dialog(int gameId,      const internal::BVValueMap& data);
        CommandRunner::Handler* equipment(int gameId,   const internal::BVValueMap& data);
        
        virtual bool init();
        BV_CREATE_FUNC(FightController);
    };
    
}


#endif /* FightController_hpp */
