//
//  GameFlowViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef GameFlowViewController_hpp
#define GameFlowViewController_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class GameFlowViewController: public UIKit::UIViewController {
    private:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(GameFlowViewController);
    };
}

#endif /* GameFlowViewController_hpp */
