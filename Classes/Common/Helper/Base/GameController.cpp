//
//  GameController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "GameController.hpp"

using namespace game;
using namespace UIKit;

GameController::GameController()
: _router(nullptr)
, delegate(nullptr) {

}

GameController::~GameController() {
    CC_SAFE_RELEASE_NULL(_router);
    
    delegate = nullptr;

    std::cout << "Destroy GameController" << std::endl;
}

bool GameController::init() {
    NetworkController::init();
    IActionController::init();
    UIViewControllerProtocol::init();
    
    _router = common::Router::create();
    return true;
}

common::Router* GameController::router() {
    return _router;
}

void GameController::processMessage(internal::network::Response& res) {
    _router->process(res);
}

void GameController::processError(internal::network::Response& res) {
    _router->error(res);
}

void GameController::log(const std::string& message) {
    std::cout << "[GameController] Log: " << message << std::endl;
}

void  GameController::stun() {
    router()->pause();
    action()->pause();
}

void GameController::exit() {
    this->stun();
    this->autorelease();
}
