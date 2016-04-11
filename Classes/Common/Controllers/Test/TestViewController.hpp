//
//  TestViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/7/16.
//
//

#ifndef TestViewController_hpp
#define TestViewController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"
#include "FightCardController.hpp"
#include "TestContainerView.hpp"

namespace game {
    
    class TestViewController: public GameViewController, public FightCardController::Delegate {
    private:
        virtual FCAT* coordinatorForPresentedCard(FightCardController& card);
    protected:
        TestContainerView* _container;
        FightCardController* _card;
        virtual void viewDidLoad();
    public:
        BV_CREATE_FUNC(TestViewController);
    };
}

#endif /* TestViewController_hpp */
