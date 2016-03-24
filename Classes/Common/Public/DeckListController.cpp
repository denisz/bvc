//
//  DeckListController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#include "DeckListController.hpp"

using namespace game;

BVValue parseDeckSave(Response *res) {
    return res->getMapByPointerAsValue("/params/deck");
};

BVValue parseDeckDelete(Response *res) {
    return BVValue::Null;
};

BVValue parseDeckList(Response *res) {
    return res->getVectorByPointerAsValue("/params/decks");
};

void DeckListController::setupEndPoints() {
    endPoint(Type::DELETE, "deck/delete", parseDeckDelete);
    endPoint(Type::UPDATE, "deck/save",   parseDeckSave);
    endPoint(Type::RELOAD, "deck/list",   parseDeckList);
}

RequestCommand* DeckListController::commandForReloadData() {
    return RequestCommand::createWithCommand("deck/list");
}