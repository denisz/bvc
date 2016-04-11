//
//  Card.cpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#include "Card.hpp"

using namespace game;

const std::string kKeyCardClassName = "card";

Card* Card::create() {
    auto ref = new Card();
    if (ref->init(kKeyCardClassName)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

Card* Card::createWithData(BVValueMap &newData) {
    auto ref = new Card();
    if (ref->initWithData(kKeyCardClassName, newData)) {
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}