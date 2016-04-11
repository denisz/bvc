//
//  AdditionalSectorView.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#include "AdditionalSectorView.hpp"

USING_NS_CC;
using namespace game;
using namespace UIKit;


void AdditionalSectorView::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::RED);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(getContentSize());
    addChild(layout);
}

void AdditionalSectorView::animateTransition(FightCardContextTransitioning* transitionContext) {
    
}