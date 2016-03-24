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
#include "FactoryControllers.h"
#include "ServiceLocator.hpp"
#include "User.hpp"

namespace game {
    class StarterViewController: public GameViewController {
    private:
        void setupView();
    protected:
        virtual void viewDidLoad();
        virtual void processOpen();
    public:
        BV_CREATE_FUNC(StarterViewController);
    };
}

#endif /* StarterViewController_hpp */
