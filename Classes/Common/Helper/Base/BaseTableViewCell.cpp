//
//  BaseTableViewCell.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "BaseTableViewCell.hpp"


using namespace game;


BaseTableViewCell::BaseTableViewCell() {
    
}

BaseTableViewCell::~BaseTableViewCell() {

}

bool BaseTableViewCell::init() {
    viewDidLoad();
    return true;
}

void BaseTableViewCell::viewDidLoad() {

}

void BaseTableViewCell::clearView() {

}

void BaseTableViewCell::prepareView(internal::BVValue *model) {

}