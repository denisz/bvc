//
//  GameController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "GameViewController.hpp"

using namespace game;
using namespace UIKit;

GameViewController::GameViewController()
: _router(nullptr)
, delegate(nullptr) {

}

GameViewController::~GameViewController() {
    CC_SAFE_RELEASE_NULL(_router);
    
    delegate = nullptr;

    std::cout << "Destroy GameController" << std::endl;
}

bool GameViewController::init() {
    UIViewController::init();
    ICommandController::init();
    IReactionController::init();
    IActionController::init();
    
    _router = common::Router::create();
    return true;
}

common::Router* GameViewController::router() {
    return _router;
}

void GameViewController::processMessage(internal::network::Response& res) {
    _router->process(res);
}

void GameViewController::processError(internal::network::Response& res) {
    _router->error(res);
}

void GameViewController::log(const std::string& message) {
    std::cout << "[GameController] Log: " << message << std::endl;
}

void GameViewController::stun() {
    router()->pause();
    action()->pause();
}

void GameViewController::exit() {
    this->stun();
    this->autorelease();
}
