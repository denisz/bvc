//
//  CemeterySectorView.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#include "CemeterySectorView.hpp"

USING_NS_CC;
using namespace game;
using namespace UIKit;

void CemeterySectorView::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::GREEN);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(getContentSize());
    addChild(layout);
}

void CemeterySectorView::animateTransition(FightCardContextTransitioning* transitionContext) {
    
}