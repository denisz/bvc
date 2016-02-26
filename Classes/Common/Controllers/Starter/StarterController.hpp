//
//  StarterController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/12/16.
//
//

#ifndef StarterController_hpp
#define StarterController_hpp

#include "stdafx.h"
#include "GameController.hpp"
#include "StarterViewController.hpp"
#include "User.hpp"


namespace game {
    class StarterController: public GameController {
    protected:
        virtual void loadViewController();
    private:
        void commandAuth(internal::network::Response* res);
        void processOpen();
    public:
        virtual bool init();
        BV_CREATE_FUNC(StarterController);
    };
}


#endif /* StarterController_hpp */
