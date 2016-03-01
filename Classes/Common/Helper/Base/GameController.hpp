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
#include "NetworkController.hpp"
#include "IActionController.hpp"
#include "UIViewController.hpp"
#include "Router.hpp"
#include "Actions.hpp"

namespace game {
    class GameController: public NetworkController, public IActionController {
    public:
        class Delegate {};
    protected:
        GameController();
        common::Router* _router;
        UIKit::UIViewController* _view;
        virtual void processMessage(internal::network::Response& res);
        virtual void processError(internal::network::Response& res);
        virtual bool init();
        virtual void loadViewController();
    public:
        ~GameController();
        void exit();
        Delegate* delegate;
        common::Router* router();
        void log(const std::string& message);
        void setView(UIKit::UIViewController* view);
        UIKit::UIViewController* getViewController();
        BV_CREATE_FUNC(GameController);
    };
}

#endif /* GameController_hpp */
