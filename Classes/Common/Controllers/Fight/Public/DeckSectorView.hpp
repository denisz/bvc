//
//  DeckSectorView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef DeckSectorView_hpp
#define DeckSectorView_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class DeckSectorView: public UIKit::UIView {
    private:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC_WITH_SIZE(DeckSectorView);
    };
}

#endif /* DeckSectorView_hpp */
