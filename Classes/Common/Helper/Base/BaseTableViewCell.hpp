//
//  BaseTableViewCell.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef BaseTableViewCell_hpp
#define BaseTableViewCell_hpp

#include "stdafx.h"
#include "UIKit.h"

USING_NS_CC_EXT;

namespace game {
    class BaseTableViewCell: public TableViewCell {
    public:
        BaseTableViewCell();
        ~BaseTableViewCell();
        
        virtual void viewDidLoad();
        virtual void prepareView(internal::BVValue* model);
        virtual void clearView();
        
        virtual bool init();
        virtual bool initWithSize(const cocos2d::Size& size);
    };
}

#endif /* BaseTableViewCell_hpp */
