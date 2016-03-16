//
//  UserFriendsController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#include "UserFriendsController.hpp"

using namespace game;

const std::string kCommandAddFriend         = "account/addFriend";
const std::string kCommandRemoveFriend      = "account/removeFriend";
const std::string kCommandAccountFriends    = "account/friends";

BVValue parseAddFriend(Response* res) {
    return res->getMapByPointerAsValue("/account");
}

BVValue parseRemoveFriend(Response* res) {
    return res->getMapByPointerAsValue("/account");
}

BVValue parseAccountFriends(Response* res) {
    return res->getVectorByPointerAsValue("/params/friends");
}

void UserFriendsController::setupEndPoints() {
    endPoint(CollectionController::Type::INSERT, kCommandAddFriend,       parseAddFriend);
    endPoint(CollectionController::Type::DELETE, kCommandRemoveFriend,    parseRemoveFriend);
    endPoint(CollectionController::Type::RELOAD, kCommandAccountFriends,  parseAccountFriends);
}

RequestCommand* UserFriendsController::commandForReloadData() {
    return RequestCommand::createWithCommand(kCommandAccountFriends);
};