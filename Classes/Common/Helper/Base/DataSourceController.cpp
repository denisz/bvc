//
//  DataSourceController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/24/16.
//
//

#include "DataSourceController.hpp"

using namespace game;


DataSourceController::DataSourceController()
: _context(nullptr) {

}

bool DataSourceController::init() {
    _context = new internal::BVValueMap();
    return GameController::init();
}