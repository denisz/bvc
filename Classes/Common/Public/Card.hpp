//
//  Card.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#ifndef Card_hpp
#define Card_hpp

#include "stdafx.h"
#include "Object.hpp"

namespace game {
    class Card: Object {
        std::string _objectIdKey = "cardid";
    public:
        static Card* create();
        static Card* createWithData(BVValueMap &newData);
    };
}

#endif /* Card_hpp */
