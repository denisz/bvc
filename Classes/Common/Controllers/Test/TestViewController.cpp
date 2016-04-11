//
//  TestViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#include "TestViewController.hpp"

USING_NS_CC;
using namespace game;


void TestViewController::viewDidLoad() {
    _card = FightCardController::createWithSize(Size(100,120));
    _card->delegate = this;
    
    _container = TestContainerView::createWithSize(Size(1024, 500));
    _container->setPosition(Vec2(0,100));
    
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    
    auto lp = ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    
    auto btn = ui::Button::create();
    btn->setLayoutParameter(lp);
    btn->setContentSize(Size(0, 0));
    btn->setTitleFontSize(20);
    btn->setTitleFontName("fonts/font.fnt");
    btn->setTitleText("CHANGE");
    
    btn->addClickEventListener([&](Ref* sender){
        
    });
    
    layout->addChild(btn);
    
    view()->addChild(layout);
    view()->addChild(_container);
    view()->addChild(_card);
}


FCAT* TestViewController::coordinatorForPresentedCard(FightCardController& card) {
    return _container;
}


