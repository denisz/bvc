//
//  GameFlowController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#include "GameFlowController.hpp"

using namespace game;


const std::string kCommandGameInit       = "game/init";
const std::string kCommandTourneySignIn  = "tournamnet/init";

GameFlowController::GameFlowController() {
    router()
        ->command(kCommandGameInit,      BV_CALLBACK_1(GameFlowController::commandGameInit, this))
        ->command(kCommandTourneySignIn, BV_CALLBACK_1(GameFlowController::commandTourneySigIn, this));
}

GameFlowController::~GameFlowController() {

}

bool GameFlowController::init() {
    return true;
}

UIKit::UIViewController* GameFlowController::loadViewController() {
    return GameFlowViewController::create();
}

bool GameFlowController::commandGameInit(internal::network::Response* res) {
    //создаем FightController
    return true;
}

bool GameFlowController::commandTourneySigIn(internal::network::Response* res) {
    //создаем TournamentController
    return true;
}
