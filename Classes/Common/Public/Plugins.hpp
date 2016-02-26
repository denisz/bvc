//
//  Plugins.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef Plugins_hpp
#define Plugins_hpp

#include "stdafx.h"
#include "UserController.hpp"
#include "CurrentUserController.hpp"
#include "DeckController.hpp"
#include "ChatController.hpp"
#include "SessionController.hpp"
#include "PvPController.hpp"
#include "BotsController.hpp"
#include "DailyController.hpp"
#include "MascotController.hpp"

#define REGISTER_GETTER_PLUGIN(__TYPE__, name) \
static __TYPE__* _##name;\
static __TYPE__* name () {\
if (Plugins::_##name == nullptr) {\
Plugins::_##name = __TYPE__::create();\
}\
return Plugins::_##name;\
}

#define IM_REGISTER_PLUGIN(__TYPE__, name)\
__TYPE__* Plugins::_##name;

namespace game {
    class Plugins {
    public:
        REGISTER_GETTER_PLUGIN(SessionController,       sessionController);
        REGISTER_GETTER_PLUGIN(DeckController,          deckController);
        REGISTER_GETTER_PLUGIN(ChatController,          chatController);
        REGISTER_GETTER_PLUGIN(UserController,          userController);
        REGISTER_GETTER_PLUGIN(CurrentUserController,   currentUserController);
        REGISTER_GETTER_PLUGIN(PvPController,           pvpController);
        REGISTER_GETTER_PLUGIN(BotsController,          botsController);
        REGISTER_GETTER_PLUGIN(DailyController,         dailyController);
        REGISTER_GETTER_PLUGIN(MascotController,        mascotController);
        
    };
}

#endif /* Plugins_hpp */
