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
    
    router()
        ->command("pvp/created", BV_CALLBACK_1(StarterController::commandAuth, this));
    
    actions()
        ->action("next", BV_CALLBACK_1(StarterController::actionNext, this));
    
    ServiceLocator::network()->connect(kServerUrl);
    
    return true;
}

void StarterController::loadViewController() {
    setView(StarterViewController::create());
}

void StarterController::processOpen() {
    User::logInWithUsernameInBackground("asd@asd.ru", "123456")->continueWithBlock([&](CommandRunner::Handler *task) -> CommandRunner::Handler* {
        
        auto user = User::currentUser();
        
        std::stringstream message;
        message << "Privet " << user->nick();
        
        Plugins::chatController()->sendPublicMessageAsync(message.str());
        
        Plugins::botsController()->getAsync()->continueWithBlock([](CommandRunner::Handler *task) ->CommandRunner::Handler* {

            if (!task->hasError()) {
                auto res = task->result();
                auto list = res->getVectorByPointer("/params/bots");
                auto botUser = User::create();
                CC_SAFE_AUTORELEASE(botUser);
                
                for (auto item:list) {
                    auto bot = item.asValueMap();
                    auto deck = bot["deck"].asValueMap();
                    auto profile = bot["profile"].asValueMap();
                    botUser->mergeFromServer(profile, true);
                    
                    std::cout << "Bot with name : " <<  botUser->nick() << std::endl;
                    
                    for (auto card: deck) {
                        std::cout << card.first << " : " << card.second.asInt() << std::endl;
                    }
                }
            }

            
            return nullptr;
        });
        
        return nullptr;
    });
}

void StarterController::commandAuth(Response* res) {
    std::cout << "Command auth" << std::endl;
}

void StarterController::actionNext(internal::ActionsClient::Event* event) {
    auto mainController = MainController::create();
    auto rootController = RootController::getInstance();
    rootController->setTop(mainController);
    exit();
}


