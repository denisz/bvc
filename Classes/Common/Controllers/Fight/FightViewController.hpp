//
//  FightViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#ifndef FightViewController_hpp
#define FightViewController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"
#include "StepFightViewController.hpp"
#include "ContextFight.hpp"

using namespace internal::network;

namespace game {
    
    class FightViewController: public StepFightViewController {
    protected:
        virtual void viewDidLoad();
        
        virtual bool initWithResponseGameInit(Response* res);
        virtual bool initWithResponseGameResume(Response* res);
        
        virtual void contextStepSetup(ContextFight        *context);
        virtual void contextStepBattle(ContextFight       *context);
        virtual void contextStepFinish(ContextFight       *context);
        virtual void contextStepChooseDeck(ContextFight   *context);
    public:
        static FightViewController* createWithResponseGameInit(Response* res);
        static FightViewController* createWithResponseGameResume(Response* res);
    };
}

#endif /* FightViewController_hpp */
