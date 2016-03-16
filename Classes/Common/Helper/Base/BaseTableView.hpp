//
//  BaseTableView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef BaseTableView_hpp
#define BaseTableView_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "IDataSourceViewController.hpp"
#include "BaseTableViewCell.hpp"

USING_NS_CC_EXT;

namespace game {
    class BaseTableView:    public IDataSourceViewController,
                            public TableViewDataSource,
                            public TableViewDelegate,
                            public UIKit::UIView {
    protected:
        cocos2d::extension::TableView* tableView;
                                
        virtual void viewDidLoad();
        virtual ssize_t numberOfCellsInTableView(TableView *table);
        virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
        virtual void tableCellTouched(TableView* table, TableViewCell* cell) {};
        virtual BaseTableViewCell* createNewCell(TableView *table, ssize_t idx);
        virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
        virtual cocos2d::Size cellSizeForTable(TableView *table);
                                
    public:
        virtual void reloadData();

        BV_CREATE_FUNC_WITH_SIZE(BaseTableView);
    };
}

#endif /* BaseTableView_hpp */
