//
//  Plugins.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/11/16.
//
//

#include "Plugins.hpp"

using namespace game;

IM_REGISTER_PLUGIN(UserController,          userController);
IM_REGISTER_PLUGIN(CurrentUserController,   currentUserController);
IM_REGISTER_PLUGIN(SessionController,       sessionController);
IM_REGISTER_PLUGIN(DeckController,          deckController);
IM_REGISTER_PLUGIN(ChatController,          chatController);
IM_REGISTER_PLUGIN(PvPController,           pvpController);
IM_REGISTER_PLUGIN(BotsController,          botsController);
IM_REGISTER_PLUGIN(DailyController,         dailyController);
IM_REGISTER_PLUGIN(MascotController,        mascotController);