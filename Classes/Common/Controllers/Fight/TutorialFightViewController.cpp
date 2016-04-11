//
//  TutorialFightViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#include "TutorialFightViewController.hpp"

using namespace game;

bool TutorialFightViewController::init() {
    if (FightViewController::init()) {
        return true;
    }
    
    return false;
}