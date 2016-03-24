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
#include "FightController.hpp"

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
        REGISTER_GETTER_PLUGIN(FightController,         fightController);
    };
}

#endif /* Plugins_hpp */
