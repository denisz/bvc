//
//  BaseTableView.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "BaseTableView.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace game;

void BaseTableView::viewDidLoad() {
    auto size = getContentSize();
    
    tableView = TableView::create(this, size);
    tableView->setDelegate(this);
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setBounceable(true);
    tableView->setPosition(Vec2::ZERO);
    this->addChild(tableView);
    tableView->reloadData();
}

//выполнять в  1 потоке
void BaseTableView::reloadData() {
    if (tableView != nullptr) {
        GCD::sendMessageToUIThread([&](){
            tableView->reloadData();
        });
    }
}

ssize_t BaseTableView::numberOfCellsInTableView(TableView *table) {
    if (_dataSource != nullptr) {
        return _dataSource->count();
    }
    return 0;
}

TableViewCell* BaseTableView::tableCellAtIndex(TableView *table, ssize_t idx) {
    if (_dataSource != nullptr) {
        auto model = _dataSource->getModelByIndex(idx);
        
        if (model != nullptr) {
            auto cell = table->dequeueCell();
            
            if (cell == nullptr) {
                auto newCell = createNewCell(table, idx);
                newCell->autorelease();
                newCell->prepareView(model);
                cell = newCell;
            } else {
                auto oldCell = dynamic_cast<BaseTableViewCell*>(cell);
                oldCell->clearView();
                oldCell->prepareView(model);
            }
            
            return cell;
        }
    }
    
    return nullptr;
}

Size BaseTableView::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return cellSizeForTable(table);
}

Size BaseTableView::cellSizeForTable(TableView *table){
    return Size(0, 40);
}

BaseTableViewCell* BaseTableView::createNewCell(TableView *table, ssize_t idx) {
    auto cell = new (std::nothrow) BaseTableViewCell();
    cell->autorelease();
    return cell;
}



