//
//  IActionController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef IActionController_hpp
#define IActionController_hpp

#include "stdafx.h"
#include "Actions.hpp"
#include "ActionsClient.hpp"
#include "ActionsRouter.hpp"

namespace game {
    class IActionController: public common::Actions::Delegate {
    private:
        common::Actions* _actions;
        common::ActionsRouter* _actionsRouter;
    protected:
        virtual void processAction(internal::ActionsClient::Event* event);
        bool _autoSubscribeAction;
    public:
        common::ActionsRouter* actions();

        IActionController();
        ~IActionController();
        
        virtual void subscribe();
        virtual void unsubscribe();
        
        bool init();
    };
}

#endif /* IActionController_hpp */
