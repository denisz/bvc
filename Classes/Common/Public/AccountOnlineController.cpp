//
//  AccountOnlineController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "AccountOnlineController.hpp"

using namespace game;

BVValue parseAccountIn(Response *res) {
    return res->getMapByPointerAsValue("/account");
};

BVValue parseAccountOut(Response *res) {
    return res->getMapByPointerAsValue("/account");
};

BVValue parseAccountChanged(Response *res) {
    return res->getMapByPointerAsValue("/profile");
};

BVValue parseAccountOnline(Response *res) {
    return res->getVectorByPointerAsValue("/params/accounts");
};

void AccountOnlineController::setupEndPoints() {
    endPoint(Type::INSERT, "account/in",                    parseAccountIn);
    endPoint(Type::DELETE, "account/out",                   parseAccountOut);
    endPoint(Type::UPDATE, "account/otherProfileChanged",   parseAccountChanged);
    endPoint(Type::RELOAD, "account/online",                parseAccountOnline);
}

RequestCommand* AccountOnlineController::commandForReloadData() {
    return RequestCommand::createWithCommand("account/online");
}

bool AccountOnlineController::isOnlineAccount(User& user) {
    return isOnlineAccountById(user.objectId());
}

bool AccountOnlineController::isOnlineAccountById(const std::string &objectId) {
    return containsModelById(objectId);
}

bool AccountOnlineController::isOnlineAccountById(int objectId) {
    return containsModelById(objectId);
}