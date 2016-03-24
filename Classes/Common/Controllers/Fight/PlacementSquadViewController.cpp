//
//  PlacementSquadViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/16/16.
//
//

#include "PlacementSquadViewController.hpp"

USING_NS_CC;
using namespace game;
using namespace UIKit;

PlacementSquadViewController::PlacementSquadViewController()
: placementDelegate(nullptr){
    
}

PlacementSquadViewController::~PlacementSquadViewController() {
    placementDelegate = nullptr;
}

PlacementSquadViewController* PlacementSquadViewController::createWithResponseGameSetup(Response* res) {
    auto ref = new PlacementSquadViewController();
    if (ref->initWithResponseGameSetup(res)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool PlacementSquadViewController::initWithResponseGameSetup(Response* res) {
    return init();
}

bool PlacementSquadViewController::init() {
    if (GameViewController::init()) {
        return true;
    }
    
    return false;
}

void PlacementSquadViewController::viewDidLoad() {
    auto layout = ui::RelativeBox::create();
    layout->setPosition(Vec2::ZERO);
    layout->setBackGroundColor(Color3B::GRAY);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setCascadeOpacityEnabled(true);
    layout->setContentSize(preferredContentSize());
    view()->addChild(layout);
    
    auto lp = ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    
    auto btn = ui::Button::create();
    btn->setLayoutParameter(lp);
    btn->setContentSize(Size(250, 50));
    btn->setTitleFontSize(24);
    btn->setTitleFontName("fonts/font.fnt");
    btn->setTitleText("Next battle");
    
    btn->addClickEventListener(BV_CALLBACK_1(PlacementSquadViewController::didTapPass, this));
    
    layout->addChild(btn);
}

void PlacementSquadViewController::didTapPass(Ref* sender) {
    if (placementDelegate != nullptr) {
        placementDelegate->handlerRequestPassSelection();
    }
}