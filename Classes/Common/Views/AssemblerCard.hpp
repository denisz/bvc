//
//  AssemblerCard.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/5/16.
//
//

#ifndef AssemblerCard_hpp
#define AssemblerCard_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class AssemblerCard: public UIKit::UIView {
    private:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC_WITH_SIZE(AssemblerCard);
    };
}

#endif /* AssemblerCard_hpp */
