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


template<class T>
class DebugControllerDelegate: public DataSourceControllerDelegate, public DataSourceViewControllerReload {
    void didChange(DataSourceController* ds, DataSourceControllerOptions options, internal::BVValue &value) {
        auto collection = dynamic_cast<T*>(ds);
        std::cout << "Change collection " << collection->count() << std::endl;
        reloadRun();
    }
};

bool MainController::init() {
    if (GameController::init()) {
        setup();
        return true;
    }
    return false;
}

void MainController::setup() {
    
    auto pvplist = PvPAvailableController::create();
    pvplist->delegate = new DebugControllerDelegate<PvPAvailableController>();
    pvplist->reloadData();
    
    auto gamelist = GameListController::create();
    gamelist->delegate = new DebugControllerDelegate<GameListController>();
    gamelist->reloadData();
    
    auto accountonline = AccountOnlineController::create();
    accountonline->delegate = new DebugControllerDelegate<AccountOnlineController>();
    accountonline->reloadData();
    
//    auto gameFlow = 
}

UIKit::UIViewController* MainController::loadViewController() {
    return MainViewController::create();
}
