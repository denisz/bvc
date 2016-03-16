//
//  TutorialFightController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/15/16.
//
//

#ifndef TutorialFightController_hpp
#define TutorialFightController_hpp

#include "stdafx.h"
#include "FightController.hpp"

namespace game {
    class TutorialFightController: public FightController {
    private:
        void commandGameTutorial(Response* res);
    public:
        BV_CREATE_FUNC(TutorialFightController);
    };
}

#endif /* TutorialFightController_hpp */
