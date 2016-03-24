//
//  GameFlowViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#include "GameFlowViewController.hpp"

USING_NS_CC;
using namespace game;

const std::string kCommandGameInit       = "game/init";
const std::string kCommandTourneySignIn  = "tournamnet/signIn";
const std::string kCommandGameResume     = "game/resume";
const std::string kCommandTourneyStatus  = "tournament/status";

#define GAMEFLOW_COMMAND(__name__) \
std::bind(&GameFlowViewController::__name__, this, std::placeholders::_1)

GameFlowViewController::GameFlowViewController() {}

GameFlowViewController::~GameFlowViewController(){
    _fights.clear();
}

bool GameFlowViewController::init() {
    if (GameViewController::init()) {
        reactionMainThread();
        
        router()
            ->command(kCommandGameInit,      GAMEFLOW_COMMAND(commandGameInit))
            ->command(kCommandTourneySignIn, GAMEFLOW_COMMAND(commandTourneySignIn))
            ->command(kCommandGameResume,    GAMEFLOW_COMMAND(commandGameResume))
            ->command(kCommandTourneyStatus, GAMEFLOW_COMMAND(commandTourneyStatus));

        return true;
    }
    
    return false;
}

void GameFlowViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    layout->setPosition(Vec2::ZERO);
    view()->addChild(layout);
    
    gameResume();
}

bool GameFlowViewController::commandGameInit(internal::network::Response* res) {
    std::lock_guard<std::mutex> lock(_mutexFights);
    
    auto fightController = FightViewController::createWithResponseGameInit(res);
    if (fightController != nullptr) {
        _fights.push_front(fightController);
        showViewController(fightController);
    }
    
    return true;
}

bool GameFlowViewController::commandGameResume(internal::network::Response* res) {
    return true;
}

bool GameFlowViewController::commandTourneyStatus(internal::network::Response *res) {
    return true;
}

void GameFlowViewController::gameResume() {
    Plugins::pvpController()->gameResume();
}

void GameFlowViewController::tourneyResume() {
    Plugins::pvpController()->tourneyResume();
}

bool GameFlowViewController::commandTourneySignIn(internal::network::Response* res) {
    std::cout << "tourney/signIn" << std::endl;
    return true;
}
