//
//  MainController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef MainController_hpp
#define MainController_hpp

#include "stdafx.h"
#include "GameController.hpp"

namespace game {
    class MainController: public GameController {
        struct Options {};
        struct States  {};
    private:
        States _states;
        Options _options;
    public:
        virtual bool init();
        BV_CREATE_FUNC(MainController);
    };
}

#endif /* MainController_hpp */
