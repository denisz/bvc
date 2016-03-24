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

bool BaseTableViewCell::initWithSize(const cocos2d::Size& size) {
    setContentSize(size);
    return init();
}

void BaseTableViewCell::viewDidLoad() {

}

void BaseTableViewCell::clearView() {

}

void BaseTableViewCell::prepareView(internal::BVValue *model) {

}