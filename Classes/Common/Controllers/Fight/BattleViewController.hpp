//
//  BattleViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#ifndef BattleViewController_hpp
#define BattleViewController_hpp

#include "stdafx.h"
#include "StepFightViewController.hpp"
#include "InputManager.hpp"
#include "AbilityClient.hpp"
#include "CemeterySectorView.hpp"
#include "BattlefieldView.hpp"
#include "AdditionalSectorView.hpp"
#include "FightCardController.hpp"

namespace game {
    class BattleViewController:
            public StepFightViewController,
            public AbilityClient::Delegate,
            public FightCardController::Delegate
    {
    private:
        virtual void viewDidLoad();

        InputManager* _inputManager;
        
        AbilityClient* _abilityClient;
        BattlefieldView* _battlefield;
        CemeterySectorView* _cemeterySector;
        AdditionalSectorView* _additionalSector;
        std::map<FightCardController::Location, FCAT*> _locations;
        
        void didTapPass(Ref* sender);
        void didTapCard(Ref* sender);
        void didTapCell(Ref* sender);
        void didTapComplete(Ref* sender);
        
//        MARK: Implementation AbilityClientDelegate
        virtual void doAbility(const internal::BVValueMap &data);
        virtual void doDialog(const internal::BVValueMap &data);
        virtual void doPass();
        
//        MARK: IMplementation FightCardControllerDelegate
        virtual FCAT* coordinatorForPresentedCard(FightCardController& card);
        
        void BeginUpdates();
        void EndUpdates();
        
        virtual void contextCreateCards(ContextFight *context);
        virtual void contextUpdateCards(ContextFight *context);
        
    public:
        BattleViewController();
        ~BattleViewController();
        
        virtual bool init();
        BV_CREATE_FUNC_WITH_FIGHT_CONTEXT(BattleViewController);
    };
}


#endif /* BattleViewController_hpp */
