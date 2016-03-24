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
#include "GameViewController.hpp"
#include "InputManager.hpp"
#include "AbilityClient.hpp"
#include "CemeterySectorView.hpp"
#include "BattlefieldView.hpp"
#include "AdditionalSectorView.hpp"

namespace game {
    class BattleViewController: public GameViewController, public AbilityClient::Delegate {
    public:
        class Delegate {
        public:
            virtual void handlerRequestPass() {};
            virtual void handlerRequestDialog(const internal::BVValueMap &data) {};
            virtual void handlerRequestAbility(const internal::BVValueMap &data) {};
        };
    private:
        AbilityClient* _abilityClient;
        InputManager* _inputManager;
        virtual void viewDidLoad();

        BattlefieldView*        _battlefield;
        CemeterySectorView*     _cemeterySector;
        AdditionalSectorView*   _additionalSector;
        
        void didTapPass(Ref* sender);
        void didTapComplete(Ref* sender);
        void didTapCard(Ref* sender);
        void didTapCell(Ref* sender);
        
//        MARK: Implementation AbilityClientDelegate
        virtual void doAbility();
        virtual void doDialog();
        virtual void doPass();
        
    public:
        virtual bool init();
        BattleViewController();
        ~BattleViewController();
        Delegate* battleDelegate;
        BV_CREATE_FUNC(BattleViewController);
    };
}


#endif /* BattleViewController_hpp */
