//
//  UserBlackListController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#include "UserBlackListController.hpp"

using namespace game;

const std::string kCommandRemoveBlacklist   = "account/removeUserIntoBlackList";
const std::string kCommandAddBlacklist      = "account/addUserIntoBlackList";
const std::string kCommandBlacklist         = "account/blacklist";

BVValue parseAddIntoBlackList(Response* res) {
    return res->getMapByPointerAsValue("/account");
}

BVValue parseRemoveIntoBlackList(Response* res) {
    return res->getMapByPointerAsValue("/account");
}

BVValue parseAccountBlacklist(Response* res) {
    return res->getVectorByPointerAsValue("/params/blackList");
}

void UserBlackListController::setupEndPoints() {
    endPoint(CollectionController::Type::INSERT, kCommandAddBlacklist,       parseAddIntoBlackList);
    endPoint(CollectionController::Type::DELETE, kCommandRemoveBlacklist,    parseRemoveIntoBlackList);
    endPoint(CollectionController::Type::RELOAD, kCommandBlacklist,          parseAccountBlacklist);
}

RequestCommand* UserBlackListController::commandForReloadData() {
    return RequestCommand::createWithCommand(kCommandBlacklist);
};