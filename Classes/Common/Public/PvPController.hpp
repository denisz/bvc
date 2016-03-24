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
        
        CommandRunner::Handler* initWithBot(const std::string& botId);
        CommandRunner::Handler* createChallenge(const internal::BVValueMap& options);
        CommandRunner::Handler* createDefaultChallenge();
        CommandRunner::Handler* acceptDuel();
        CommandRunner::Handler* denyDuel();
        CommandRunner::Handler* join(const std::string& gameId);
        CommandRunner::Handler* cancel();
        CommandRunner::Handler* cancelRandom();
        CommandRunner::Handler* hasCreated();
        CommandRunner::Handler* hasRandom();
        CommandRunner::Handler* random();
        CommandRunner::Handler* gameResume();
        CommandRunner::Handler* tourneyResume();
        
        virtual bool init();
        BV_CREATE_FUNC(PvPController);
    };
}

#endif /* PvPController_hpp */
