//
//  TestContainerView.cpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#include "TestContainerView.hpp"

USING_NS_CC;
using namespace game;


bool TestContainerView::init() {
    _gridBase = Geometry::GridBase::createWithSizeCell(100, 100);
    return true;
}

TestContainerView::~TestContainerView() {
    CC_SAFE_RELEASE_NULL(_gridBase);
}

void TestContainerView::viewDidLoad() {
    setCascadeOpacityEnabled(true);
    
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::GREEN);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(getContentSize());

    addChild(layout);
}

cocos2d::Vec2 TestContainerView::getCoordinateByXAndY(int x, int y) {
    return _gridBase->pointByIndexPath(x, y).toVec2();
}

void TestContainerView::animateTransition(FightCardContextTransitioning* transitionContext) {
    //делаем анимацию
    auto card = transitionContext->card();
    auto point = getCoordinateByXAndY(card->getX(), card->getY());
}