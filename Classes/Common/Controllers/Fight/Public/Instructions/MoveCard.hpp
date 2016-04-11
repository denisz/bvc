//
//  MoveCard.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/9/16.
//
//

#ifndef MoveCard_hpp
#define MoveCard_hpp

#include "stdafx.h"

namespace game {
    class MoveCard: Instructions::Instruction {
    private:
        virtual void serve();
    public:
        bool init();
        BV_CREATE_FUNC(MoveCard);
    };
}

#endif /* MoveCard_hpp */
