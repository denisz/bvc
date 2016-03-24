//
//  GameController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include "stdafx.h"
#include "IReactionController.hpp"
#include "ICommandController.hpp"
#include "IActionController.hpp"
#include "UIKit.h"
#include "Router.hpp"
#include "Actions.hpp"

using namespace internal::network;
using namespace common;

namespace game {
    class GameViewController:   public UIKit::UIViewController,
                                public IReactionController,
                                public ICommandController,
                                public IActionController {
    public:
        class Delegate {};
    private:
        Router* _router;
    protected:
        GameViewController();

        virtual void processMessage(Response& res);
        virtual void processError(Response& res);
        virtual bool init();
    public:
        ~GameViewController();
        Delegate* delegate;
        Router* router();
        
        void exit();
        void stun();
        void log(const std::string& message);
        
        BV_CREATE_FUNC(GameViewController);
    };
}

#endif /* GameController_hpp */
