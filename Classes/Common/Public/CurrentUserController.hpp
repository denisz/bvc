//
//  CurrentUserController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef CurrentUserController_hpp
#define CurrentUserController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class CurrentUserController: public internal::AIRef, public ICommandController {
    public:
        CommandRunner::Handler* logInAsync(const std::string &login, const std::string &password);
        CommandRunner::Handler* signUpAsync(const std::string &login, const std::string &password);
        CommandRunner::Handler* logOutAsync();
        CommandRunner::Handler* requestPasswordResetAsync();
        CommandRunner::Handler* removeFriends(const std::string &profileId);
        CommandRunner::Handler* addFriends(const std::string &profileId);
        CommandRunner::Handler* removeFromBlacklist(const std::string &profileId);
        CommandRunner::Handler* addToBlacklist(const std::string &profileId);
        CommandRunner::Handler* friends();
        CommandRunner::Handler* blacklist();
        
        bool init();
        BV_CREATE_FUNC(CurrentUserController);
    };
}

#endif /* CurrentUserController_hpp */
