//
//  TutorialFightViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#include "TutorialFightViewController.hpp"

using namespace game;

const std::string kCommandGameTutorial = "game/tutorial";
#define FIGHT_TUTORIAL_COMMAND(__name__) std::bind(&TutorialFightViewController::__name__, this, std::placeholders::_1)

bool TutorialFightViewController::init() {
    if (FightViewController::init()) {
        auto valid = BV_CALLBACK_1(TutorialFightViewController::validResponseCommand, this);
        
        router()
            ->command(kCommandGameTutorial, { valid, FIGHT_TUTORIAL_COMMAND(commandGameTutorial) });
        return true;
    }
    
    return false;
}

bool TutorialFightViewController::validResponseCommand(Response* res) {
    return FightViewController::validResponseCommand(res);
}

bool TutorialFightViewController::commandGameTutorial(Response* res) {
    return true;
}