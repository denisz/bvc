//
//  AssemblerCard.cpp
//  bvunity
//
//  Created by denis zaytcev on 4/5/16.
//
//

#include "AssemblerCard.hpp"

USING_NS_CC;
using namespace game;

void AssemblerCard::viewDidLoad() {
    setCascadeOpacityEnabled(true);
    
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::RED);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(getContentSize());
    addChild(layout);
}