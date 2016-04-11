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
        static User* _currentUser;
        static std::mutex _mutexCurrentUser;
        static void setCurrentUser(User* user);
        static UserController* userController();
        static CurrentUserController* currentUserController();
    public:
        static User* currentUser();
        static CommandRunner::Handler* logInWithUsernameInBackground(const std::string &login, const std::string &password);
        static CommandRunner::Handler* logOutInBackground();
        static CommandRunner::Handler* getAsync(const std::string& profileId);
        
        void saveEventually();
        void deleteEventually();
        
        CommandRunner::Handler* saveInBackground();
        CommandRunner::Handler* deleteInBackground();
        
        const int level() const;
        const std::string nick() const;
        const std::string avatar() const;
        bool isCurrentUser(User& user);
        
        static User* create();
        static User* createWithData(BVValueMap &newData);
    };
}

#endif /* User_hpp */
