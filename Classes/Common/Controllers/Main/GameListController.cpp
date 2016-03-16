//
//  GameListController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "GameListController.hpp"

using namespace game;

BVValue parseGameStarted(Response *res) {
    return res->getMapByPointerAsValue("/game");
};

BVValue parseGameFinished(Response *res) {
    return res->getMapByPointerAsValue("/game");
};

BVValue parsePvPList(Response *res) {
    return res->getVectorByPointerAsValue("/params/games");
};

void GameListController::setupEndPoints() {
    endPoint(Type::INSERT, "game/started",  parseGameStarted);
    endPoint(Type::DELETE, "game/finished", parseGameFinished);
    endPoint(Type::RELOAD, "pvp/list",      parsePvPList);
}

RequestCommand* GameListController::commandForReloadData() {
    return RequestCommand::createWithCommand("pvp/list");
}