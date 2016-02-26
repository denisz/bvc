//
//  StarterViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#ifndef StarterViewController_hpp
#define StarterViewController_hpp

#include "stdafx.h"
#include "BaseUIViewController.hpp"

namespace game {
    class StarterViewController: public game::BaseUIViewController {
    protected:
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(StarterViewController);
    };
}

#endif /* StarterViewController_hpp */
