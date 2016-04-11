//
//  TransferCard.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/9/16.
//
//

#ifndef TransferCard_hpp
#define TransferCard_hpp

#include "stdafx.h"

namespace game {
    class TransferCard: Instructions::Instruction {
    private:
        virtual void serve();
    public:
        bool init();
        BV_CREATE_FUNC(TransferCard);
    };
}


#endif /* TransferCard_hpp */
