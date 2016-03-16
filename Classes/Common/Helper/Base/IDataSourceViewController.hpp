//
//  IDataSourceViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/10/16.
//
//

#ifndef IDataSourceViewController_hpp
#define IDataSourceViewController_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "DataSourceController.hpp"

namespace game {
    class IDataSourceViewController {
    protected:
        DataSourceViewControllerReload* _reloadDelegate;
        DataSourceViewControllerDelegate* _dataSource;
    public:
        IDataSourceViewController();
        ~IDataSourceViewController();
        virtual void reloadData();
        
        void setReloadDelegate(DataSourceViewControllerReload* reloadDelegate);
        void setDataSource(DataSourceViewControllerDelegate* dataSource);
    };
}

#endif /* IDataSourceViewController_hpp */
