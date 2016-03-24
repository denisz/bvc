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
    private:
        cocos2d::extension::TableView* tableView;
    protected:
                                
        virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
        virtual cocos2d::Size cellSizeForTable(TableView *table);
        virtual void tableCellTouched(TableView* table, TableViewCell* cell);
        virtual ssize_t numberOfCellsInTableView(TableView *table);
        virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);

        virtual void viewDidLoad();
        virtual BaseTableViewCell* createNewCell(TableView *table, ssize_t idx);
        virtual int heightForRowAtIndexPath(TableView *table, ssize_t idx);
        virtual bool willSelectRowAtIndex(TableView *table, ssize_t idx);
        virtual void didSelectRowAtIndex(TableView *table, ssize_t idx);
        virtual BVValue* getModelByIndex(ssize_t idx);

    public:
        virtual void reloadData();

        BV_CREATE_FUNC_WITH_SIZE(BaseTableView);
    };
}

#endif /* BaseTableView_hpp */
