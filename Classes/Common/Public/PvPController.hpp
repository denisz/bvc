//
//  PvPController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef PvPController_hpp
#define PvPController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class PvPController: public internal::AIRef, public ICommandController {
    public:
        
        CommandRunner::Handler* cancel();
        CommandRunner::Handler* random();
        CommandRunner::Handler* denyDuel();
        CommandRunner::Handler* hasRandom();
        CommandRunner::Handler* acceptDuel();
        CommandRunner::Handler* hasCreated();
        CommandRunner::Handler* gameResume();
        CommandRunner::Handler* cancelRandom();
        CommandRunner::Handler* tourneyResume();
        CommandRunner::Handler* createDefaultChallenge();
        
        CommandRunner::Handler* join(const std::string& gameId);
        CommandRunner::Handler* initWithBot(const std::string& botId);
        CommandRunner::Handler* createChallenge(const internal::BVValueMap& options);
        
        virtual bool init();
        BV_CREATE_FUNC(PvPController);
    };
}

#endif /* PvPController_hpp */
