//
//  User.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef User_hpp
#define User_hpp

#include "stdafx.h"
#include "Plugins.hpp"
#include "Utils.hpp"
#include "Object.hpp"

using namespace internal;

namespace game {
    class User: public game::Object {
    private:
        static UserController* userController();
        static CurrentUserController* currentUserController();
        static std::mutex _mutexCurrentUser;
        static User* _currentUser;
        static void setCurrentUser(User* user);    
    public:
        static User* currentUser();
        static CommandRunner::Handler* logInWithUsernameInBackground(const std::string &login, const std::string &password);
        static CommandRunner::Handler* logOutInBackground();
        static CommandRunner::Handler* getAsync(const std::string& profileId);
        
        CommandRunner::Handler* saveInBackground();
        void saveEventually();
        CommandRunner::Handler* deleteInBackground();
        void deleteEventually();

        
        const std::string nick() const;
        const int level() const;
        const std::string avatar() const;
        bool isCurrentUser(User& user);
        
        static User* create();
    };
}

#endif /* User_hpp */
