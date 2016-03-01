//
//  MainController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "MainController.hpp"


using namespace game;
using namespace UIKit;

bool MainController::init() {
    return GameController::init();
}

void MainController::loadViewController() {
    setView(MainViewController::create());
}
