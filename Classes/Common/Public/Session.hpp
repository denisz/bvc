//
//  Session.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/19/16.
//
//

#ifndef Session_hpp
#define Session_hpp

#include "stdafx.h"
#include "Plugins.hpp"
#include "Object.hpp"

using namespace internal;

namespace game {
    class Session: public game::Object {
    private:
        static SessionController* sessionController();
    public:
        CommandRunner::Handler* checkInBackground();
    };
}

#endif /* Session_hpp */
