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

using namespace internal::network;
using namespace common;

namespace game {
    class GameViewController: public NetworkController, public IActionController, public UIKit::UIViewControllerProtocol {
    public:
        class Delegate {};
    private:
        Router* _router;
    protected:
        GameController();

        virtual void processMessage(Response& res);
        virtual void processError(Response& res);
        virtual bool init();
    public:
        ~GameController();
        Delegate* delegate;
        Router* router();
        
        void exit();
        void stun();
        void log(const std::string& message);
        
        BV_CREATE_FUNC(GameController);
    };
}

#endif /* GameController_hpp */
