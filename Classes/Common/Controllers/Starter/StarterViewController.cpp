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
using namespace UIKit;

void StarterViewController::viewDidLoad() {
    auto layout = ui::Layout::create();
    layout->setCascadeOpacityEnabled(true);
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setPosition(Vec2(10,10));
    layout->setSize(Size(1004, 748));
    
    auto sprite = Sprite::create("logo.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(Vec2(0, 0));
    layout->addChild(sprite);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        
        if (bounds.containsPoint(touch->getLocation())){
            std::cout << "Click" << std::endl;
            auto event = ServiceLocator::actionsClient()->createEventWithCommand("next");
            CC_SAFE_AUTORELEASE(event);
            ServiceLocator::actionsClient()->call(event);
        }
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,sprite);

    view()->addChild(layout);
}