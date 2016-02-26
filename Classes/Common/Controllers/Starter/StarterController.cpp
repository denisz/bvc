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
    
    _router->command("pvp/created",
                     BV_CALLBACK_1(StarterController::commandAuth, this) );

    ServiceLocator::network()->connect(kServerUrl);
    
    return true;
}

void StarterController::loadViewController() {
    auto view = StarterViewController::create();
    setView(view);
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
        
//        Plugins::pvpController()->random();
//        Plugins::pvpController()->createDefaultChallenge();
        
//        std::async([](){
//            Plugins::pvpController()->hasCreated()->continueWithBlock([](CommandRunner::Handler *task)-> CommandRunner::Handler* {
//                auto res = task->result();
//                auto result = res->getBoolByPointerWithDefault("/params/result", false);
//                std::cout << std::to_string(result) << std::endl;
//                return nullptr;
//            });
//        });
        
        return nullptr;
    });
}

void StarterController::commandAuth(Response* res) {
    std::cout << "Command auth" << std::endl;
}
