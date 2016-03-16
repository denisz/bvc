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
: _router(nullptr)
, delegate(nullptr) {

}

DataSourceController::~DataSourceController() {
    CC_SAFE_RELEASE_NULL(_router);
    delegate = nullptr;
}

bool DataSourceController::init() {
    _router = Router::create();
    return NetworkController::init();
}

common::Router* DataSourceController::router() {
    return _router;
}

void DataSourceController::processMessage(internal::network::Response& res) {
    _router->process(res);
}

void DataSourceController::processError(internal::network::Response& res) {
    _router->error(res);
}
