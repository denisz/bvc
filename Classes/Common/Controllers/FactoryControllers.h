//
//  FactoryControllers.h
//  bvunity
//
//  Created by denis zaytcev on 3/1/16.
//
//

#ifndef FactoryControllers_h
#define FactoryControllers_h

#include "stdafx.h"
#include "GameViewController.hpp"

namespace game {
    class RootViewController;
    class StarterViewController;
    class MainViewController;
    class ArenaViewController;
    class FightViewController;
    class TutorialFightViewController;
    class GameFlowViewController;
    class ChooseDeckViewController;
    class PlacementSquadViewController;
    class BattleViewController;
    
#ifdef BV_DEBUG
    class TestViewController;
#endif
}

#include "StarterViewController.hpp"
#include "ArenaViewController.hpp"
#include "ChooseDeckViewController.hpp"
#include "PlacementSquadViewController.hpp"
#include "BattleViewController.hpp"
#include "GameFlowViewController.hpp"
#include "MainViewController.hpp"
#include "RootViewController.hpp"
#include "FightViewController.hpp"
//#include "TutorialFightViewController.hpp"


#ifdef BV_DEBUG
#include "TestViewController.hpp"
#endif

#endif /* FactoryControllers_h */
