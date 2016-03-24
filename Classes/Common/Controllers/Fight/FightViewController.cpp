//
//  FightViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "FightViewController.hpp"

USING_NS_CC;

const std::string kDefaultStage = "default";
const std::string kKeyStage     = "stage";
const std::string kKeyCardId    = "cardid";
const std::string kKeyAblId     = "id";

using namespace game;
using namespace UIKit;

#define FC(__name__) std::bind(&FightViewController::__name__, this, std::placeholders::_1)

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

void FightViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    layout->setPosition(Vec2(0,0));
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    
    view()->addChild(layout);
}

bool FightViewController::initWithResponse(Response* res) {
    if (FightViewController::init()) {
        
        auto gameId     = res->getNumberByPointerWithDefault("/params/gameid", -1);
        auto gameType   = res->getStringByPointerWithDefault("/params/gameType", "");
        auto player     = res->getMapByPointer("/params/player");
        auto opponent   = res->getMapByPointer("/params/opponent");
        
        if (gameType.empty() || gameId < 0|| player.empty() || opponent.empty()) {
            return false;
        }
        
        _gameData.opponent          = User::createWithData(opponent);
        _gameData.player            = User::createWithData(player);
        _gameData.gameType          = gameType;
        _gameData.gameId            = gameId;
        _gameData.cards             = std::map<int, BVValue>();
        _gameData.abilities         = std::map<int, BVValue>();
        _gameData.ablWithTargets    = std::forward_list<BVValue>();
        _gameData.logs              = std::vector<std::string>();
        
        return true;
    }
    return false;
}

FightViewController* FightViewController::createWithResponseGameInit(Response* res) {
    auto ref = new FightViewController();
    if (ref->initWithResponse(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

FightViewController* FightViewController::createWithResponseResume(Response* res) {
    auto ref = new FightViewController();
    if (ref->initWithResponse(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool FightViewController::init() {
    if (GameViewController::init()) {
        
        _gameData = GameData();
        
        auto valid       = FC(validResponseCommand);
        auto updateStage = FC(middlewareUpdateStage);
        
        router()
        ->command(kCommandGameEquip,       { valid, FC(commandGameEquipment),   updateStage     })
        ->command(kCommandGameBegin,       { valid, FC(commandGameBegin),       updateStage     })
        ->command(kCommandGameCreateAbl,   { valid, FC(commandGameCreateAbl),   updateStage     })
        ->command(kCommandGameCreateCards, { valid, FC(commandGameCreateCards), updateStage     })
        ->command(kCommandGameDeleteCards, { valid, FC(commandGameDeleteCards), updateStage     })
        ->command(kCommandGameUpdateCards, { valid, FC(commandGameUpdateCards), updateStage     })
        ->command(kCommandGameUpdateCards, { valid, FC(commandGameUpdateAbl),   updateStage     })
        ->command(kCommandGameDeleteAbl,   { valid, FC(commandGameDeleteAbl),   updateStage     })
        ->command(kCommandGameChooseDeck,  { valid, FC(commandGameChooseDeck)    })
        ->command(kCommandGameSetup,       { valid, FC(commandGameSetup)         })
        ->command(kCommandGameTimers,      { valid, FC(commandGameTimers)        })
        ->command(kCommandGameLog,         { valid, FC(commandGameLog)           })
        ->command(kCommandGameDialog,      { valid, FC(commandGameDialog)        })
        ->command(kCommandGameOfferDraw,   { valid, FC(commandGameOfferDraw)     })
        ->command(kCommandGameCancelDraw,  { valid, FC(commandGameCancelDraw)    })
        ->command(kCommandGameFinish,      { valid, FC(commandGameFinish)        });
        
        ServiceLocator::network()->connect(kServerUrl);
        return true;
    }
    
    return false;
}

bool FightViewController::validResponseCommand(Response* res) {
    auto gameid = res->getNumberByPointerWithDefault("/id", -1);
    return _gameData.gameId == gameid;
}

bool FightViewController::commandGameFinish(Response* res) {
    return true;
}


bool FightViewController::commandGameEquipment(Response* res) {
    return true;
}

bool FightViewController::commandGameBegin(Response* res) {
    GCD::sendMessageToUIThread([&](){
        auto controller = BattleViewController::create();
        controller->battleDelegate = this;
        presentViewController(controller, true);
    });
    return true;
}

bool FightViewController::commandGameChooseDeck(Response* res) {
    GCD::sendMessageToUIThread([&](){
        auto controller = ChooseDeckViewController::createWithResponseChooseDeck(res);
        controller->deckDelegate = this;
        presentViewController(controller, true);
    });
    return true;
}

bool FightViewController::commandGameSetup(Response* res) {
    GCD::sendMessageToUIThread([&](){
        auto controller = PlacementSquadViewController::createWithResponseGameSetup(res);
        controller->placementDelegate = this;
        presentViewController(controller, true);
    });
    return true;
}

bool FightViewController::commandGameTimers(Response* res) {
    return true;
}

bool FightViewController::commandGameCreateCards(Response* res) {
    auto created = res->getVectorByPointer("/created");
    
    for (auto &item: created) {
        if (item.getType() == BVValue::Type::MAP) {
            auto itemData   = item.asValueMap();
            auto find       = itemData.find(kKeyCardId);
            if (find != itemData.end()) {
                _gameData.cards.emplace(std::make_pair(find->second.asInt(), item));
            }
        }
    }

    return true;
}

bool FightViewController::commandGameDeleteCards(Response* res) {
    return true;
}

bool FightViewController::commandGameCreateAbl(Response* res) {
    auto created = res->getVectorByPointer("/created");
    for (auto &item: created) {
        if (item.getType() == BVValue::Type::MAP) {
            auto itemData   = item.asValueMap();
            auto find       = itemData.find(kKeyAblId);
            if (find != itemData.end()) {
                _gameData.abilities.emplace(std::make_pair(find->second.asInt(), item));
            }
        }
    }
    
    return true;
}

bool FightViewController::commandGameDeleteAbl(Response* res) {
    return true;
}

bool FightViewController::commandGameLog(Response* res) {
    
    return true;
}

bool FightViewController::commandGameUpdateCards(Response* res) {
    auto cards = res->getVectorByPointer("/updated");
    for (auto &item: cards) {
        if (item.getType() == BVValue::Type::MAP) {
            auto itemData   = item.asValueMap();
            auto find       = itemData.find(kKeyCardId);
            if (find != itemData.end()) {
                auto card = _gameData.cards.find(find->second.asInt());
                if (card != _gameData.cards.end()) {
                    extendBVValue(card->second, itemData);
                }
            }
        }
    }
    
    return true;
}

bool FightViewController::commandGameUpdateAbl(Response* res) {
    _gameData.ablWithTargets.clear();
    
    auto abls  = res->getVectorByPointer("/abilities");
    for (auto &item: abls) {
        _gameData.ablWithTargets.push_front(item);
    }

    return true;
}

bool FightViewController::middlewareUpdateStage(Response* res) {
    _gameData.stage = res->getStringByPointerWithDefault("/stage", kDefaultStage);
    return true;
}

bool FightViewController::commandGameDialog(Response* res) {
    return true;
}

bool FightViewController::commandGameOfferDraw(Response* res) {
    return true;
}

bool FightViewController::commandGameCancelDraw(Response* res) {
    return true;
}

bool FightViewController::commandError(Response* res) {
    return true;
}

int FightViewController::gameId() {
    return _gameData.gameId;
}


//MARK: Implementation viewControllers delegates
void FightViewController::handlerRequestChooseDeck(int deckId){
    Plugins::fightController()->chooseDeck(gameId(), deckId);
}

void FightViewController::handlerRequestPassSelection() {
    Plugins::fightController()->pass(gameId());
}

void FightViewController::handlerRequestSelectionSquad(const BVValueVector &selection) {
    Plugins::fightController()->selection(gameId(), selection);
}

void FightViewController::handlerRequestDialog(const internal::BVValueMap &data) {
    Plugins::fightController()->dialog(gameId(), data);
}

void FightViewController::handlerRequestAbility(const internal::BVValueMap &data) {
    Plugins::fightController()->ability(gameId(), data);
}

void FightViewController::handlerRequestPass() {
    Plugins::fightController()->pass(gameId());
}