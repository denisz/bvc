//
//  FightController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "FightController.hpp"


using namespace game;

#define FIGHT_COMMAND(__name__) std::bind(&FightController::__name__, this, std::placeholders::_1)

const std::string kCommandGameFinish        = "game/finish";
const std::string kCommandGameEquip         = "game/equipment";
const std::string kCommandGameChooseDeck    = "game/choosedeck";
const std::string kCommandGameSetup         = "game/setup";
const std::string kCommandGameTimers        = "game/timers";
const std::string kCommandGameCreateCards   = "game/createCards";
const std::string kCommandGameDeleteCards   = "game/deleteCards";
const std::string kCommandGameCreateAbl     = "game/createabilities";
const std::string kCommandGameDeleteAbl     = "game/deleteabilities";
const std::string kCommandGameLog           = "game/log";
const std::string kCommandGameUpdateCards   = "game/updatecards";
const std::string kCommandGameDialog        = "game/dialog";
const std::string kCommandGameOfferDraw     = "game/offerDraw";
const std::string kCommandGameCancelDraw    = "game/cancelDraw";

UIKit::UIViewController* FightController::loadViewController() {
    return FightViewController::create();
}

bool FightController::init() {
    GameController::init();

    auto valid = BV_CALLBACK_1(FightController::checkFightController, this);
    
    router()
        ->command(kCommandGameEquip,       { valid, FIGHT_COMMAND(commandGameEquipment)     })
        ->command(kCommandGameFinish,      { valid, FIGHT_COMMAND(commandGameFinish)        })
        ->command(kCommandGameCreateAbl,   { valid, FIGHT_COMMAND(commandGameCreateAbl)     })
        ->command(kCommandGameDeleteAbl,   { valid, FIGHT_COMMAND(commandGameDeleteAbl)     })
        ->command(kCommandGameChooseDeck,  { valid, FIGHT_COMMAND(commandGameChooseDeck)    })
        ->command(kCommandGameCreateCards, { valid, FIGHT_COMMAND(commandGameCreateCards)   })
        ->command(kCommandGameDeleteCards, { valid, FIGHT_COMMAND(commandGameDeleteCards)   })
        ->command(kCommandGameUpdateCards, { valid, FIGHT_COMMAND(commandGameUpdateCards)   })
        ->command(kCommandGameSetup,       { valid, FIGHT_COMMAND(commandGameSetup)         })
        ->command(kCommandGameTimers,      { valid, FIGHT_COMMAND(commandGameTimers)        })
        ->command(kCommandGameLog,         { valid, FIGHT_COMMAND(commandGameLog)           })
        ->command(kCommandGameDialog,      { valid, FIGHT_COMMAND(commandGameDialog)        })
        ->command(kCommandGameOfferDraw,   { valid, FIGHT_COMMAND(commandGameOfferDraw)     })
        ->command(kCommandGameCancelDraw,  { valid, FIGHT_COMMAND(commandGameCancelDraw)    });
    
    ServiceLocator::network()->connect(kServerUrl);
    
    return true;
}

bool FightController::checkFightController(Response* res) {
    return true;
}

bool FightController::commandGameFinish(Response* res) {
    return true;
}

bool FightController::commandGameEquipment(Response* res) {
    return true;
}

bool FightController::commandGameChooseDeck(Response* res) {
    return true;
}

bool FightController::commandGameSetup(Response* res) {
    return true;
}

bool FightController::commandGameTimers(Response* res) {
    return true;
}

bool FightController::commandGameCreateCards(Response* res) {
    return true;
}

bool FightController::commandGameDeleteCards(Response* res) {
    return true;
}

bool FightController::commandGameCreateAbl(Response* res) {
    return true;
}

bool FightController::commandGameDeleteAbl(Response* res) {
    return true;
}

bool FightController::commandGameLog(Response* res) {
    return true;
}

bool FightController::commandGameUpdateCards(Response* res) {
    return true;
}

bool FightController::commandGameDialog(Response* res) {
    return true;
}

bool FightController::commandGameOfferDraw(Response* res) {
    return true;
}

bool FightController::commandGameCancelDraw(Response* res) {
    return true;
}

bool FightController::error(Response* res) {
    return true;
}
