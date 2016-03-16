//
//  PvPAvailableController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "PvPAvailableController.hpp"

using namespace game;

BVValue parsePvPCreatedResponse(Response* res) {
    return res->getMapByPointerAsValue("/pvp");
}

BVValue parsePvPRemovedResponse(Response* res) {
    return res->getMapByPointerAsValue("/pvp");
}

BVValue parsePvPAvailableResponse(Response* res) {
    return res->getVectorByPointerAsValue("/params/games");
}

void PvPAvailableController::setupEndPoints() {
    endPoint(CollectionController::Type::INSERT, "pvp/created",   parsePvPCreatedResponse);
    endPoint(CollectionController::Type::DELETE, "pvp/removed",   parsePvPRemovedResponse);
    endPoint(CollectionController::Type::RELOAD, "pvp/available", parsePvPAvailableResponse);
}

RequestCommand* PvPAvailableController::commandForReloadData() {
    return RequestCommand::createWithCommand("pvp/available");
};