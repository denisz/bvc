//
//  TutorialFightViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#ifndef TutorialFightViewController_hpp
#define TutorialFightViewController_hpp

#include "stdafx.h"
#include "FactoryControllers.h"

namespace game {
    class TutorialFightViewController: public FightViewController {
    protected:
        virtual bool init();
    public:
        
        BV_CREATE_FUNC(TutorialFightViewController);
    };
}

#endif /* TutorialFightViewController_hpp */
