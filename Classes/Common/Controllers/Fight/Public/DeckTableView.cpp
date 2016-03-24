//
//  DeckTableView.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#include "DeckTableView.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace game;

void DeckTableView::viewDidLoad() {
    BaseTableView::viewDidLoad();
}

BaseTableViewCell* DeckTableView::createNewCell(TableView *table, ssize_t idx) {
    auto size = tableCellSizeForIndex(table, idx);
    return DeckTableViewCell::createWithSize(size);
}

int DeckTableView::heightForRowAtIndexPath(TableView *table, ssize_t idx) {
    return 100;
}

void DeckTableViewCell::viewDidLoad() {
    auto text = ui::TextBMFont::create("String", "fonts/font.fnt");
    text->setPosition(Vec2(50, 50));
    
    auto bg = ui::Layout::create();
    
    bg->setBackGroundColor(Color3B::GREEN);
    bg->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    bg->setSizePercent(Vec2::ANCHOR_TOP_RIGHT);
    bg->setSizeType(cocos2d::ui::Widget::SizeType::PERCENT);
    bg->setPosition(Vec2::ZERO);
    
    addChild(bg);
    addChild(text);
}

void DeckTableViewCell::prepareView(internal::BVValue *model) {
    
}
void DeckTableView::didSelectRowAtIndex(TableView *table, ssize_t idx) {
    if (delegate != nullptr) {
        auto model = getModelByIndex(idx);
        if (model != nullptr) {
            if (delegate->tryChooseDeck(*model)) {
                delegate->didSelectedDeck(*model);
            }
        }
    }
}