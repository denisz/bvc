//
//  FightViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#ifndef FightViewController_hpp
#define FightViewController_hpp

#include "stdafx.h"
#include "UIKit.h"

namespace game {
    class FightViewController: public UIKit::UIViewController {
    protected:
        virtual void viewDidLoad();
        
    public:
        BV_CREATE_FUNC(FightViewController);
    };
}

#endif /* FightViewController_hpp */
