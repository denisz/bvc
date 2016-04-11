//
//  ContextFight.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/25/16.
//
//

#include "ContextFight.hpp"


using namespace game;

const std::string kDefaultStage = "default";
const std::string kKeyStage     = "stage";
const std::string kKeyCardId    = "cardid";
const std::string kKeyAblId     = "id";

#define CF(__name__) std::bind(&ContextFight::__name__, this, std::placeholders::_1)

const std::string kCommandGameFinish        = "game/finish";
const std::string kCommandGameBegin         = "game/createcards";
const std::string kCommandGameEquip         = "game/equipment";
const std::string kCommandGameChooseDeck    = "game/choosedeck";
const std::string kCommandGameSetup         = "game/setup";
const std::string kCommandGameTimers        = "game/timers";
const std::string kCommandGameCreateCards   = "game/createcards";
const std::string kCommandGameDeleteCards   = "game/deletecards";
const std::string kCommandGameCreateAbl     = "game/createabilities";
const std::string kCommandGameDeleteAbl     = "game/deleteabilities";
const std::string kCommandGameLog           = "game/log";
const std::string kCommandGameUpdateCards   = "game/updatecards";
const std::string kCommandGameDialog        = "game/dialog";
const std::string kCommandGameOfferDraw     = "game/offerDraw";
const std::string kCommandGameCancelDraw    = "game/cancelDraw";
const std::string kCommandGameTutorial      = "game/tutorial";

ContextFight::ContextFight() {
    
}

ContextFight::~ContextFight() {

}

bool ContextFight::initWithResponseGameResume(Response *res) {
    if (ContextFight::init()) {
        return true;
    }
    
    return false;
}

bool ContextFight::initWithResponseGameInit(Response *res) {
    if (ContextFight::init()) {
        auto gameId     = res->getNumberByPointerWithDefault("/params/gameid", -1);
        auto gameType   = res->getStringByPointerWithDefault("/params/gameType", "");
        auto player     = res->getMapByPointer("/params/player");
        auto opponent   = res->getMapByPointer("/params/opponent");
        
        if (gameType.empty() || gameId < 0 || player.empty() || opponent.empty()) {
            return false;
        }
        
        _gameDB.opponent          = User::createWithData(opponent);
        _gameDB.player            = User::createWithData(player);
        _gameDB.gameType          = gameType;
        _gameDB.gameId            = gameId;
        _gameDB.cards             = std::map<int, BVValue>();
        _gameDB.abilities         = std::map<int, BVValue>();
        _gameDB.ablWithTargets    = std::forward_list<BVValue>();
        _gameDB.logs              = std::vector<std::string>();
        _gameDB.hand              = std::map<std::string, int>();
        
        return true;
    }
    
    return false;
}

bool ContextFight::init() {
    if (DataSourceController::init()) {
        _gameDB = GameDB();
        
        auto valid          = CF(validResponseCommand);
        auto updateStage    = CF(middlewareUpdateStage);
        
        router()
        ->command(kCommandGameEquip,       { valid, CF(commandGameEquipment),   updateStage     })
        ->command(kCommandGameBegin,       { valid, CF(commandGameBegin),       updateStage     })
        ->command(kCommandGameCreateAbl,   { valid, CF(commandGameCreateAbl),   updateStage     })
        ->command(kCommandGameCreateCards, { valid, CF(commandGameCreateCards), updateStage     })
        ->command(kCommandGameDeleteCards, { valid, CF(commandGameDeleteCards), updateStage     })
        ->command(kCommandGameUpdateCards, { valid, CF(commandGameUpdateCards), updateStage     })
        ->command(kCommandGameUpdateCards, { valid, CF(commandGameUpdateAbl),   updateStage     })
        ->command(kCommandGameDeleteAbl,   { valid, CF(commandGameDeleteAbl),   updateStage     })
        ->command(kCommandGameChooseDeck,  { valid, CF(commandGameChooseDeck)    })
        ->command(kCommandGameSetup,       { valid, CF(commandGameSetup)         })
        ->command(kCommandGameTimers,      { valid, CF(commandGameTimers)        })
        ->command(kCommandGameLog,         { valid, CF(commandGameLog)           })
        ->command(kCommandGameDialog,      { valid, CF(commandGameDialog)        })
        ->command(kCommandGameOfferDraw,   { valid, CF(commandGameOfferDraw)     })
        ->command(kCommandGameCancelDraw,  { valid, CF(commandGameCancelDraw)    })
        ->command(kCommandGameFinish,      { valid, CF(commandGameFinish)        });
        

        return true;
    }
    
    return false;
}

bool ContextFight::validResponseCommand(Response* res) {
    auto gameid = res->getNumberByPointerWithDefault("/id", -1);
    return _gameDB.gameId == gameid;
}

bool ContextFight::commandGameFinish(Response* res) {
    notify(&ContextFightEvents::contextStepFinish, this);
    return true;
}

bool ContextFight::commandGameEquipment(Response* res) {
    notify(&ContextFightEvents::contextStepEquipment, this);
    return true;
}

bool ContextFight::commandGameBegin(Response* res) {
    notify(&ContextFightEvents::contextStepBattle, this);
    return true;
}

bool ContextFight::commandGameChooseDeck(Response* res) {
    notify(&ContextFightEvents::contextStepChooseDeck, this);
    return true;
}

bool ContextFight::commandGameSetup(Response* res) {
    auto hand = res->getMapByPointer("/hand");
    if (hand.empty()) {
        return false;
    }
    
    _gameDB.hand.clear();
    
    for (auto &item: hand) {
        _gameDB.hand[item.first] = item.second.asInt();
    }
    
    _gameDB.gold        = res->getNumberByPointerWithDefault("/gold",       0);
    _gameDB.deals       = res->getNumberByPointerWithDefault("/gold.deals", 0);
    _gameDB.silver      = res->getNumberByPointerWithDefault("/silver",     0);
    _gameDB.timer1      = res->getNumberByPointerWithDefault("/timer/t1",   0);
    _gameDB.timer2      = res->getNumberByPointerWithDefault("/timer/t2",   0);
    _gameDB.firstTurn   = res->getNumberByPointerWithDefault("/silver.second", 0) != 0;
    
    notify(&ContextFightEvents::contextStepSetup, this);
    notify(&ContextFightEvents::contextUpdateSetup, this);
    
    return true;
}

bool ContextFight::commandGameTimers(Response* res) {
    _gameDB.timer1      = res->getNumberByPointerWithDefault("/timer/t1",   0);
    _gameDB.timer2      = res->getNumberByPointerWithDefault("/timer/t2",   0);

    return true;
}

bool ContextFight::commandGameCreateCards(Response* res) {
    auto created = res->getVectorByPointer("/created");
    if (!created.empty()) {
        for (auto &item: created) {
            if (item.getType() == BVValue::Type::MAP) {
                auto itemData   = item.asValueMap();
                auto find       = itemData.find(kKeyCardId);
                if (find != itemData.end()) {
                    _gameDB.cards.emplace(std::make_pair(find->second.asInt(), item));
                }
            }
        }
        notify(&ContextFightEvents::contextCreateCards, this);
    }
    
    return true;
}

bool ContextFight::commandGameDeleteCards(Response* res) {
    return true;
}

bool ContextFight::commandGameCreateAbl(Response* res) {
    auto created = res->getVectorByPointer("/created");
    
    if (!created.empty()) {
        for (auto &item: created) {
            if (item.getType() == BVValue::Type::MAP) {
                auto itemData   = item.asValueMap();
                auto find       = itemData.find(kKeyAblId);
                if (find != itemData.end()) {
                    _gameDB.abilities.emplace(std::make_pair(find->second.asInt(), item));
                }
            }
        }
    }
    
    return true;
}

bool ContextFight::commandGameDeleteAbl(Response* res) {
    return true;
}

bool ContextFight::commandGameLog(Response* res) {
    
    return true;
}

bool ContextFight::commandGameUpdateCards(Response* res) {
    auto cards = res->getVectorByPointer("/updated");
    if (!cards.empty()) {
        for (auto &item: cards) {
            if (item.getType() == BVValue::Type::MAP) {
                auto itemData   = item.asValueMap();
                auto find       = itemData.find(kKeyCardId);
                if (find != itemData.end()) {
                    auto card = _gameDB.cards.find(find->second.asInt());
                    if (card != _gameDB.cards.end()) {
                        extendBVValue(card->second, itemData);
                    }
                }
            }
        }
        
        notify(&ContextFightEvents::contextUpdateCards, this);
    }
    
    return true;
}

bool ContextFight::commandGameUpdateAbl(Response* res) {
    _gameDB.ablWithTargets.clear();
    
    auto abls  = res->getVectorByPointer("/abilities");
    if (!abls.empty()) {
        for (auto &item: abls) {
            _gameDB.ablWithTargets.push_front(item);
        }
        notify(&ContextFightEvents::contextUpdateAbl, this);
    }
    
    return true;
}

bool ContextFight::middlewareUpdateStage(Response* res) {
    _gameDB.stage = res->getStringByPointerWithDefault("/stage", kDefaultStage);
    notify(&ContextFightEvents::contextUpdateStage, this);
    return true;
}

bool ContextFight::commandGameDialog(Response* res) {
    return true;
}

bool ContextFight::commandGameOfferDraw(Response* res) {
    return true;
}

bool ContextFight::commandGameCancelDraw(Response* res) {
    return true;
}

bool ContextFight::commandError(Response* res) {
    return true;
}

int ContextFight::gameId() {
    return _gameDB.gameId;
}

GameDB ContextFight::db() {
    return _gameDB;
}

void ContextFight::handlerRequestChooseDeck(int deckId){
    Plugins::fightController()->chooseDeck(gameId(), deckId);
}

void ContextFight::handlerRequestPassSelection() {
    Plugins::fightController()->pass(gameId());
}

void ContextFight::handlerRequestSelectionSquad(const BVValueVector &selection) {
    Plugins::fightController()->selection(gameId(), selection);
}

void ContextFight::handlerRequestDialog(const internal::BVValueMap &data) {
    Plugins::fightController()->dialog(gameId(), data);
}

void ContextFight::handlerRequestAbility(const internal::BVValueMap &data) {
    Plugins::fightController()->ability(gameId(), data);
}

void ContextFight::handlerRequestPass() {
    Plugins::fightController()->pass(gameId());
}

ContextFight* ContextFight::createWithResponseGameInit(Response* res) {
    auto ref = new ContextFight();
    if (ref->initWithResponseGameInit(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

ContextFight* ContextFight::createWithResponseGameResume(Response* res) {
    auto ref = new ContextFight();
    if (ref->initWithResponseGameResume(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}