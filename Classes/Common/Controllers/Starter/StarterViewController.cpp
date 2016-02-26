//
//  StarterViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "StarterViewController.hpp"

USING_NS_CC;

using namespace game;

void StarterViewController::viewDidLoad() {
    auto layout = ui::Layout::create();
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setPosition(Vec2(10,10));
    layout->setSize(Size(1004, 748));
    
    auto sprite = Sprite::create("logo.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(Vec2(0, 0));
    layout->addChild(sprite);
    
    view()->addChild(layout);
}