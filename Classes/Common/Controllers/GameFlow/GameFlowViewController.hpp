//
//  GameFlowViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef GameFlowViewController_hpp
#define GameFlowViewController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"

namespace game {
    class GameFlowViewController: public GameViewController {
    private:
        std::mutex _mutexFights;
        std::forward_list<FightViewController*> _fights;
        
        bool commandGameInit(internal::network::Response* res);
        bool commandGameResume(internal::network::Response* res);
        bool commandTourneySignIn(internal::network::Response* res);
        bool commandTourneyStatus(internal::network::Response* res);


        virtual void viewDidLoad();
    protected:
        virtual bool init();
    public:
        GameFlowViewController();
        ~GameFlowViewController();
        
        void gameResume();
        void tourneyResume();
        
        BV_CREATE_FUNC_WITH_SIZE(GameFlowViewController);
    };
}

#endif /* GameFlowViewController_hpp */
