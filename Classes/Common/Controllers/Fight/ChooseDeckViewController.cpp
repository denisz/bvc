//
//  ChooseDeckViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/16/16.
//
//

#include "ChooseDeckViewController.hpp"

USING_NS_CC;
using namespace game;
using namespace UIKit;

void ChooseDeckViewController::viewDidLoad() {
    auto deckList = DeckListController::create();
    deckList->delegate = this;
    
    auto deckTableView = DeckTableView::createWithSize(preferredContentSize());
    deckTableView->setBackGroundColor(Color3B::GRAY);
    deckTableView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    deckTableView->setDataSource(deckList);
    deckTableView->setReloadDelegate(this);
    deckTableView->delegate = this;
    deckTableView->setPosition(Vec2::ZERO);
    view()->addChild(deckTableView);
    
    deckList->reloadData();
}

void ChooseDeckViewController::didChange(DataSourceController* ds, DSOptions options, BVValue &value) {
    auto collection = (DeckListController*)ds;
    std::cout << "Change deck list " << collection->count() << std::endl;
    reloadTableView();
}

bool ChooseDeckViewController::tryChooseDeck(const BVValue &deck) {
    return true;
}

void ChooseDeckViewController::didSelectedDeck(const BVValue &deck) {
    auto deckClass = Deck::create();
    CC_SAFE_AUTORELEASE(deckClass);
    deckClass->mergeFromServer(deck);
    auto deckId = deckClass->objectIdAsInt();
    context()->handlerRequestChooseDeck(deckId);
}
