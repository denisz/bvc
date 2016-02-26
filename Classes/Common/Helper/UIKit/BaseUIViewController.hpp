//
//  BaseUIViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef BaseUIViewController_hpp
#define BaseUIViewController_hpp

#include "stdafx.h"
#include "UIViewController.hpp"
#include "TransitionManager.hpp"


namespace game {
    class BaseUIViewController: public UIViewController {
    protected:
        virtual bool init();
    public:
        BV_CREATE_FUNC(BaseUIViewController);
    };
}

#endif /* BaseUIViewController_hpp */
