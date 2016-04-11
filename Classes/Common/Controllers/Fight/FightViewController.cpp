//
//  FightViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "FightViewController.hpp"

USING_NS_CC;

using namespace game;
using namespace UIKit;

void FightViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    layout->setPosition(Vec2(0,0));
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    
    view()->addChild(layout);
}

void FightViewController::contextStepChooseDeck(ContextFight   *context) {
    GCD::sendMessageToUIThread([&](){
        auto controller = ChooseDeckViewController::createWithFightContext(this->context());
        presentViewController(controller, true);
    });
};

void FightViewController::contextStepSetup(ContextFight  *context) {
    GCD::sendMessageToUIThread([&](){
        auto controller = PlacementSquadViewController::createWithFightContext(this->context());
        presentViewController(controller, true);
    });
};

void FightViewController::contextStepBattle(ContextFight *context) {
    GCD::sendMessageToUIThread([&](){
        auto controller = BattleViewController::createWithFightContext(this->context());
        presentViewController(controller, true);
    });
};

void FightViewController::contextStepFinish(ContextFight *context) {
    
};


bool FightViewController::initWithResponseGameInit(Response* res) {
    if (FightViewController::init()) {
        auto contextFight = ContextFight::createWithResponseGameInit(res);
        CC_SAFE_AUTORELEASE(contextFight);
        return initWithContextFight(contextFight);
    }
    return false;
}

bool FightViewController::initWithResponseGameResume(Response* res) {
    if (FightViewController::init()) {
        auto contextFight = ContextFight::createWithResponseGameResume(res);
        CC_SAFE_AUTORELEASE(contextFight);
        return initWithContextFight(contextFight);
    }
    return false;
}

FightViewController* FightViewController::createWithResponseGameInit(Response* res) {
    auto ref = new FightViewController();
    if (ref->initWithResponseGameInit(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

FightViewController* FightViewController::createWithResponseGameResume(Response* res) {
    auto ref = new FightViewController();
    if (ref->initWithResponseGameResume(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}