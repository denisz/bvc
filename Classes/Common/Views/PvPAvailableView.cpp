//
//  PvPAvailableView.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "PvPAvailableView.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace game;

void PvPAvailableView::viewDidLoad() {
    BaseTableView::viewDidLoad();
    
    this->setBackGroundColor(cocos2d::Color3B::GRAY);
    this->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
}

BaseTableViewCell* PvPAvailableView::createNewCell(TableView *table, ssize_t idx) {
    return PvPAvailableTableViewCell::create();
}

void PvPAvailableTableViewCell::viewDidLoad() {
    auto size = Size(300, 40);
    auto _size = getContentSize();
    
    auto text = ui::TextBMFont::create("String", "fonts/font.fnt");
    text->setPosition(Vec2(50, 50));

    auto bg = ui::Layout::create();

    bg->setBackGroundColor(Color3B::GREEN);
    bg->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    bg->setContentSize(size);
    bg->setPosition(Vec2::ZERO);
    
    addChild(bg);
    addChild(text);
}

void PvPAvailableTableViewCell::prepareView(internal::BVValue *model) {
    
}