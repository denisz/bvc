//
//  MainViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/7/16.
//
//

#include "MainViewController.hpp"
USING_NS_CC;

using namespace game;
using namespace UIKit;

void MainViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(Size(1024, 768));
    layout->setPosition(Vec2(0,0));
    view()->addChild(layout);
    
    auto size = Size(200, 150);

    auto lpItem = ui::LinearLayoutParameter::create();
    lpItem->setMargin(ui::Margin(10,0,0,0));
    lpItem->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::RIGHT);
    
    auto item1 = ui::Button::create();
    item1->setTitleText("PVP");
    item1->setTitleFontSize(48);
    item1->setTitleColor(cocos2d::Color3B::WHITE);
    item1->setTitleFontName("fonts/arial.ttf");
    item1->addClickEventListener(CC_CALLBACK_1(MainViewController::onDidTapBattlesWithPlayers, this));
    item1->setLayoutParameter(lpItem->clone());
    item1->setContentSize(size);
    item1->setCascadeOpacityEnabled(true);
    
    auto item2 = ui::Button::create();
    item2->setTitleText("Random");
    item2->setTitleFontSize(48);
    item2->setTitleColor(cocos2d::Color3B::WHITE);
    item2->setTitleFontName("fonts/arial.ttf");
    item2->addClickEventListener(CC_CALLBACK_1(MainViewController::onDidTapRandom, this));
    item2->setLayoutParameter(lpItem->clone());
    item2->setContentSize(size);
    item2->setCascadeOpacityEnabled(true);
    
    auto item3 = ui::Button::create();
    item3->setTitleText("Tourney");
    item3->setTitleFontSize(48);
    item3->setTitleColor(cocos2d::Color3B::WHITE);
    item3->setTitleFontName("fonts/arial.ttf");
    item3->addClickEventListener(CC_CALLBACK_1(MainViewController::onDidTapTourney, this));
    item3->setLayoutParameter(lpItem->clone());
    item3->setContentSize(size);
    item3->setCascadeOpacityEnabled(true);

    auto item4 = ui::Button::create();
    item4->setTitleText("Bots");
    item4->setTitleFontSize(48);
    item4->setTitleColor(cocos2d::Color3B::WHITE);
    item4->setTitleFontName("fonts/arial.ttf");
    item4->addClickEventListener(CC_CALLBACK_1(MainViewController::onDidTapBattleWithBots, this));
    item4->setLayoutParameter(lpItem->clone());
    item4->setContentSize(size);
    item4->setCascadeOpacityEnabled(true);

    auto lpw = ui::RelativeLayoutParameter::create();
    lpw->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
    
    auto menu = ui::HBox::create();
    menu->setAnchorPoint(Vec2(0,0));
    menu->setContentSize(Size(size.width * 4, 150));
    menu->setCascadeOpacityEnabled(true);
    menu->addChild(item1);
    menu->addChild(item2);
    menu->addChild(item3);
    menu->addChild(item4);
    
    menu->setLayoutParameter(lpw);
    
    layout->addChild(menu);
}

void MainViewController::onDidTapBattlesWithPlayers(Ref* sender) {
    std::cout << "onDidTapBattlesWithPlayers" << std::endl;
}

void MainViewController::onDidTapRandom(Ref* sender) {
    std::cout << "onDidTapRandom" << std::endl;
    
    auto actionClient = ServiceLocator::actionsClient();
    auto event = actionClient->createEventWithCommand("init/randomBattle");
    CC_SAFE_AUTORELEASE(event);
    actionClient->call(event);
}

void MainViewController::onDidTapTourney(Ref* sender) {
    std::cout << "onDidTapTourney" << std::endl;
}

void MainViewController::onDidTapClans(Ref* sender) {
    std::cout << "onDidTapClans" << std::endl;
}

void MainViewController::onDidTapBattleWithBots(Ref* sender) {
    std::cout << "onDidTapBattleWithBots" << std::endl;
}
