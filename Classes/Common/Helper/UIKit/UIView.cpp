//
//  UIView.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "UIView.hpp"

using namespace UIKit;

bool UIView::init() {
    if (Layout::init()) {
        viewDidLoad();
        return true;
    }
    
    return false;
}

bool UIView::initWithSize(const cocos2d::Size &contentSize) {
    if (Layout::init()) {
        setContentSize(contentSize);
        viewDidLoad();
        return true;
    }
    
    return false;
}

void UIView::viewDidLoad() {}