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
, _view(nullptr)
, delegate(nullptr) {

}

GameController::~GameController() {
    CC_SAFE_RELEASE_NULL(_view);
    CC_SAFE_RELEASE_NULL(_router);
    
    delegate = nullptr;
}

bool GameController::init() {
    NetworkController::init();
    IActionController::init();
    
    _router = common::Router::create();
    loadViewController();
    return true;
}

void GameController::loadViewController() {}

UIViewController* GameController::getViewController() {
    return _view;
}

void GameController::setView(UIViewController* view) {
    _view = view;
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
    std::cout << "Log: " << message << std::endl;
}

void GameController::exit() {
    this->autorelease();
}
