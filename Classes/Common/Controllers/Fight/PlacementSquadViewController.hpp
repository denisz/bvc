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
#include "StepFightViewController.hpp"

namespace game {
    class PlacementSquadViewController: public StepFightViewController {
    public:
    private:
        virtual void viewDidLoad();
        void didTapPass(Ref* sender);
    public:
        BV_CREATE_FUNC_WITH_FIGHT_CONTEXT(PlacementSquadViewController);
    };
}

#endif /* PlacementSquadViewController_hpp */
