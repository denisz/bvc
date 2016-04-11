//
//  ContextFightViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/25/16.
//
//

#ifndef ContextFightViewController_hpp
#define ContextFightViewController_hpp

#include "stdafx.h"
#include "DataSourceController.hpp"
#include "User.hpp"

namespace game {
    class ContextFight;
    
    class GameDB {
    public:
        User* player;
        User* opponent;
        std::string stage;
        std::string gameType;
        
        std::map<int, BVValue> cards;
        std::vector<std::string> logs;
        std::map<std::string, int> hand;
        std::map<int, BVValue> abilities;
        std::forward_list<BVValue> ablWithTargets;
        
        int gold        = 0;
        int deals       = 0;
        int gameId      = 0;
        int silver      = 0;
        time_t timer1   = 0;
        time_t timer2   = 0;
        bool firstTurn  = false;
    };
    
    class ContextFightEvents: public BaseObserverProtocol {
    public:
        virtual void contextStepSetup(ContextFight          *context) {};
        virtual void contextStepBattle(ContextFight         *context) {};
        virtual void contextStepFinish(ContextFight         *context) {};
        virtual void contextStepEquipment(ContextFight      *context) {};
        virtual void contextStepChooseDeck(ContextFight     *context) {};
        virtual void contextUpdateStage(ContextFight        *context) {};
        virtual void contextCreateCards(ContextFight        *context) {};
        virtual void contextUpdateCards(ContextFight        *context) {};
        virtual void contextUpdateAbl(ContextFight          *context) {};
        virtual void contextUpdateTimer(ContextFight        *context) {};
        virtual void contextUpdateSetup(ContextFight        *context) {};
    };
    
    class ContextFight: public DataSourceController, public Observable<ContextFightEvents> {
    private:
        GameDB _gameDB;
        
        bool commandGameLog(Response* res);
        bool commandGameSetup(Response* res);
        bool commandGameBegin(Response* res);
        bool commandGameFinish(Response* res);
        bool commandGameTimers(Response* res);
        bool commandGameDialog(Response* res);
        bool commandGameEquipment(Response* res);
        bool commandGameCreateAbl(Response* res);
        bool commandGameDeleteAbl(Response* res);
        bool commandGameUpdateAbl(Response* res);
        bool commandGameOfferDraw(Response* res);
        bool validResponseCommand(Response* res);
        bool commandGameChooseDeck(Response* res);
        bool commandGameCancelDraw(Response* res);
        bool middlewareUpdateStage(Response* res);
        bool commandGameCreateCards(Response* res);
        bool commandGameDeleteCards(Response* res);
        bool commandGameUpdateCards(Response* res);
        
        bool commandError(Response* res);
    public:
        ContextFight();
        ~ContextFight();
        
        virtual bool init();
        virtual bool initWithResponseGameInit(Response* res);
        virtual bool initWithResponseGameResume(Response* res);
        
        int gameId();
        
        GameDB db();

        virtual void handlerRequestPass();
        virtual void handlerRequestPassSelection();
        virtual void handlerRequestChooseDeck(int deckId);
        virtual void handlerRequestDialog(const internal::BVValueMap &data);
        virtual void handlerRequestAbility(const internal::BVValueMap &data);
        virtual void handlerRequestSelectionSquad(const BVValueVector &selection);
        
        static ContextFight* createWithResponseGameInit(Response* res);
        static ContextFight* createWithResponseGameResume(Response* res);
    };
}

#endif /* ContextFightViewController_hpp */
