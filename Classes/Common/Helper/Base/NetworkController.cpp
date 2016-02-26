//
//  NetworkController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "NetworkController.hpp"

using namespace game;

bool NetworkController::init()
{
    ICommandController::init();
    IReactionController::init();
    return true;
}