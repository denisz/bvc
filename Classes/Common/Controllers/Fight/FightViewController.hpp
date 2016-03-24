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
#include "User.hpp"

using namespace internal::network;

namespace game {
    
    
    
    class FightViewController:
                public GameViewController,
                public ChooseDeckViewController::Delegate,
                public PlacementSquadViewController::Delegate,
                public BattleViewController::Delegate
    {
    public:
        struct GameData {
            std::map<int, BVValue> cards;
            std::map<int, BVValue> abilities;
            std::forward_list<BVValue> ablWithTargets;
            std::vector<std::string> logs;
            time_t timer;
            std::string gameType;
            User* player;
            User* opponent;
            int gameId;
            std::string stage;
        };
    private:
        GameData _gameData;
        
//        MARK: Implementation delegate ChooseViewController
        virtual void handlerRequestChooseDeck(int deckId);
        
//        MARK: Implementation delegate PlacementSquadViewController
        virtual void handlerRequestPassSelection();
        virtual void handlerRequestSelectionSquad(const BVValueVector &selection);
        
//        MARK: Implementation delegate BattleViewController
        virtual void handlerRequestPass();
        virtual void handlerRequestDialog(const internal::BVValueMap &data);
        virtual void handlerRequestAbility(const internal::BVValueMap &data);

    protected:
        virtual bool validResponseCommand(Response* res);
        virtual void viewDidLoad();
        
//        MARK: Implementation commands
        bool commandGameFinish(Response* res);
        bool commandGameBegin(Response* res);
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
        bool commandGameUpdateAbl(Response* res);
        bool commandGameDialog(Response* res);
        bool commandGameOfferDraw(Response* res);
        bool commandGameCancelDraw(Response* res);
        bool middlewareUpdateStage(Response* res);
        
        bool commandError(Response* res);
        
//        MARK: Initialize
        virtual bool init();
        virtual bool initWithResponse(Response* res);
    public:
        int gameId();
        
        static FightViewController* createWithResponseGameInit(Response* res);
        static FightViewController* createWithResponseResume(Response* res);
    };
}

#endif /* FightViewController_hpp */
