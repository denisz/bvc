
//
//  StarterViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "StarterViewController.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace game;
using namespace UIKit;

void StarterViewController::viewDidLoad() {
    auto layout = ui::Layout::create();
    layout->setPosition(Vec2(0,0));
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(Size(1004, 748));
    layout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    view()->addChild(layout);
    
    auto lp = ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    
    auto btn = ui::Button::create();
    btn->setLayoutParameter(lp);
    btn->setContentSize(Size(250, 50));
    btn->setTitleFontSize(24);
    btn->setTitleFontName("fonts/font.fnt");
    btn->setTitleText("Start");
    
    btn->addClickEventListener([](Ref* sender){
        auto actionClient = ServiceLocator::actionsClient();
        auto event = actionClient->createEventWithCommand("start");
        CC_SAFE_AUTORELEASE(event);
        actionClient->call(event);
    });
    
    
    layout->addChild(btn);
}