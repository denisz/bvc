//
//  Session.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/19/16.
//
//

#include "Session.hpp"

using namespace internal;
using namespace game;

SessionController* Session::sessionController() {
    return Plugins::sessionController();
}

CommandRunner::Handler* Session::checkInBackground() {
    return sessionController()->checkSessionTokenAsync();
}
