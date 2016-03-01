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
    auto layout = ui::Layout::create();
    layout->setBackGroundColor(Color3B::RED);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setPosition(Vec2(10,10));
    layout->setSize(Size(1004, 748));
    
    view()->addChild(layout);
}