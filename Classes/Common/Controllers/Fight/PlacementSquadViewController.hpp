//
//  PlacementSquadViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/16/16.
//
//

#ifndef PlacementSquadViewController_hpp
#define PlacementSquadViewController_hpp

#include "stdafx.h"
#include "GameViewController.hpp"

namespace game {
    class PlacementSquadViewController: public GameViewController {
    public:
        class Delegate {
        public:
            virtual void handlerRequestPassSelection() {};
            virtual void handlerRequestSelectionSquad(const BVValueVector &selection) {};
        };
    private:
        virtual void viewDidLoad();
        void didTapPass(Ref* sender);
    public:
        virtual bool init();
        virtual bool initWithResponseGameSetup(Response* res);
        PlacementSquadViewController();
        ~PlacementSquadViewController();
        Delegate* placementDelegate;
        static PlacementSquadViewController* createWithResponseGameSetup(Response* res);
    };
}

#endif /* PlacementSquadViewController_hpp */
