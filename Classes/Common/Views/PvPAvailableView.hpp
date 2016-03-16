//
//  PvPAvailableView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef PvPAvailableView_hpp
#define PvPAvailableView_hpp

#include "stdafx.h"
#include "BaseTableView.hpp"

namespace game {
    
    class PvPAvailableTableViewCell: public BaseTableViewCell {
    public:
        virtual void viewDidLoad();
        virtual void prepareView(internal::BVValue* model);
        BV_CREATE_FUNC(PvPAvailableTableViewCell)
    };
    
    class PvPAvailableView: public BaseTableView  {
    private:
        virtual void viewDidLoad();
        virtual BaseTableViewCell* createNewCell(TableView *table, ssize_t idx);
    public:
        BV_CREATE_FUNC_WITH_SIZE(PvPAvailableView);
    };
}

#endif /* PvPAvailableView_hpp */
