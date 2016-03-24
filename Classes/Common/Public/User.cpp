//
//  User.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "User.hpp"

using namespace internal;
using namespace game;


const std::string kKeyUserClassName = "user";

User* User::_currentUser;
std::mutex User::_mutexCurrentUser;

User* User::create() {
    auto user = new User();
    if (user->init(kKeyUserClassName)) {
        return user;
    }
    
    CC_SAFE_DELETE(user);
    return nullptr;
}

User* User::createWithData(BVValueMap &newData) {
    auto user = new User();
    if (user->initWithData(kKeyUserClassName, newData)) {
        return user;
    }
    
    CC_SAFE_DELETE(user);
    return nullptr;
}

UserController* User::userController() {
    return Plugins::userController();
}

CurrentUserController* User::currentUserController() {
    return Plugins::currentUserController();
}

User* User::currentUser() {
    std::lock_guard<std::mutex> lock(_mutexCurrentUser);
    return _currentUser;
}

void User::setCurrentUser(User* user) {
    std::lock_guard<std::mutex> lock(_mutexCurrentUser);
    
    if (_currentUser != nullptr) {
        CC_SAFE_RELEASE_NULL(_currentUser);
    }
    
    _currentUser = user;
}

CommandRunner::Handler* User::logInWithUsernameInBackground(const std::string& login, const std::string& password) {
    
    return currentUserController()->logInAsync(login, password)->continueWithBlock([&](CommandRunner::Handler *task) -> CommandRunner::Handler* {
        
        if (!task->hasError()) {
            auto res = task->result();            
            auto newData = res->getMapByPointer("/params/profile");
            auto user = User::create();
            user->mergeFromServer(newData);
            User::setCurrentUser(user);
        }
        
        return nullptr;
    });
}

CommandRunner::Handler* User::logOutInBackground() {
    return currentUserController()->logOutAsync()->continueWithBlock([&](CommandRunner::Handler *task) -> CommandRunner::Handler* {
        CC_SAFE_RELEASE_NULL(User::_currentUser);
        return nullptr;
    });
}

CommandRunner::Handler* User::getAsync(const std::string& profileId) {
    return userController()->getAsync(profileId);
}

bool User::isCurrentUser(User& user) {
    return *this == user;
}

const std::string User::nick() const {
    return valueForKey("nick", kHiddenUserName).asString();
}

const int User::level() const {
    return valueForKey("level", 0).asInt();
}

const std::string User::avatar() const {
    return valueForKey("avatar", kHiddenUserAvatar).asString();
}
