//
//  NewsController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/23/16.
//
//

#include "NewsController.hpp"

using namespace game;

BVValue parseNewsResponse(Response* res) {
    return res->getVectorByPointerAsValue("/news");
}

void NewsController::setupEndPoints() {
    endPoint(CollectionController::Type::RELOAD, "server/welcome", parseNewsResponse);
}