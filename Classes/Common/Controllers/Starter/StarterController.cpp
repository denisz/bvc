//
//  StarterController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/12/16.
//
//

#include "StarterController.hpp"

using namespace game;
using namespace internal::network;

bool StarterController::init() {
    GameController::init();
    
    action()
        ->action("start", BV_CALLBACK_1(StarterController::actionStart, this));

    ServiceLocator::network()->connect(kServerUrl);
    
    return true;
}

UIKit::UIViewController* StarterController::loadViewController() {
    return StarterViewController::create();
}

void StarterController::processOpen() {
    //если нету загрузить AuthController
    
    User::logInWithUsernameInBackground("asd@asd.ru", "123456")->continueWithBlock([&](CommandRunner::Handler *task) -> CommandRunner::Handler* {
        
        auto user = User::currentUser();
        
        std::stringstream message;
        message << "Privet " << user->nick();
        
        Plugins::chatController()->sendPublicMessageAsync(message.str());
        
        return nullptr;
    });
}

void StarterController::actionStart(internal::ActionsClient::Event* event) {
    auto controller = MainController::create();
    auto rootController = RootController::getInstance();
    rootController->presentController(controller, this);
}


