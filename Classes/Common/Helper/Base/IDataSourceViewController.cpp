//
//  DataSourceViewController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/10/16.
//
//

#include "IDataSourceViewController.hpp"

using namespace game;

IDataSourceViewController::IDataSourceViewController()
: _dataSource(nullptr)
, _reloadDelegate(nullptr) {
}

IDataSourceViewController::~IDataSourceViewController() {
    _dataSource = nullptr;
    
    _reloadDelegate->reloadCallback = nullptr;
    _reloadDelegate = nullptr;
}

void IDataSourceViewController::setDataSource(DataSourceViewControllerDelegate* dataSource) {
    _dataSource = dataSource;
}

void IDataSourceViewController::setReloadDelegate(DataSourceViewControllerReload* reloadDelegate) {
    _reloadDelegate = reloadDelegate;
    _reloadDelegate->reloadCallback = CC_CALLBACK_0(IDataSourceViewController::reloadData, this);
}

void IDataSourceViewController::reloadData() {}