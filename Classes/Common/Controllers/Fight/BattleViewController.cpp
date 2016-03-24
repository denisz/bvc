//
//  BattleViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#include "BattleViewController.hpp"

USING_NS_CC;
using namespace game;
using namespace UIKit;

BattleViewController::BattleViewController()
: battleDelegate(nullptr)
, _abilityClient(nullptr)
, _inputManager(nullptr) {
    
}

BattleViewController::~BattleViewController() {
    battleDelegate = nullptr;
    CC_SAFE_RELEASE_NULL(_inputManager);
    CC_SAFE_RELEASE_NULL(_abilityClient);
    
    CC_SAFE_RELEASE_NULL(_battlefield);
    CC_SAFE_RELEASE_NULL(_additionalSector);
    CC_SAFE_RELEASE_NULL(_cemeterySector);
}

bool BattleViewController::init() {
    if (GameViewController::init()) {
        _inputManager  = InputManager::create();
        
        _abilityClient = AbilityClient::create();
        _inputManager->addDelegate(_abilityClient);
        
        return true;
    }
    
    return false;
}

void BattleViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::BLUE);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    view()->addChild(layout);
    
    auto lp = ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    
    auto btn = ui::Button::create();
    btn->setLayoutParameter(lp);
    btn->setContentSize(Size(250, 50));
    btn->setTitleFontSize(24);
    btn->setTitleFontName("fonts/font.fnt");
    btn->setTitleText("Pass");
    
    btn->addClickEventListener(BV_CALLBACK_1(BattleViewController::didTapPass, this));
    
    layout->addChild(btn);
}


void BattleViewController::didTapCard(Ref* sender) {
    _inputManager->didTapCard(10);
}

void BattleViewController::didTapCell(Ref* sender) {
    _inputManager->didTapCell(1, 1);
}

void BattleViewController::didTapPass(Ref* sender) {
    _inputManager->didTapPass();
}

void BattleViewController::didTapComplete(Ref* sender) {
    _inputManager->didTapComplete();
}

void BattleViewController::doAbility() {
    auto data = BVValueMap();
    battleDelegate->handlerRequestAbility(data);
}

void BattleViewController::doDialog() {
    auto data = BVValueMap();
    battleDelegate->handlerRequestDialog(data);
}

void BattleViewController::doPass() {
    battleDelegate->handlerRequestPass();
}