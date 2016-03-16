//
//  DataSourceController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/24/16.
//
//

#ifndef DataSourceController_hpp
#define DataSourceController_hpp

#include "stdafx.h"
#include "NetworkController.hpp"
#include "Router.hpp"

namespace game {
    class DataSourceController;
    
    class DataSourceViewControllerDelegate {
    public:
        virtual int count() = 0;
        virtual  internal::BVValue* getModelByIndex(ssize_t index) = 0;
    };
    
    enum class DataSourceControllerOptions {INSERT, RELOAD, UPDATE, DELETE};
    
    class DataSourceViewControllerReload {
    protected:
        void reloadRun() {
            if (reloadCallback) reloadCallback();
        }
    public:
         std::function<void()> reloadCallback;
    };
    
    class DataSourceControllerDelegate {
    public:
        virtual void didChange(DataSourceController* ds, DataSourceControllerOptions options, BVValue &value) {};
        virtual void willChange(DataSourceController* ds, DataSourceControllerOptions options, BVValue &value) {};
    };
    
    class DataSourceController: public NetworkController {
    protected:
        virtual void processMessage(internal::network::Response& res);
        virtual void processError(internal::network::Response& res);
        virtual bool init();
        Router* _router;
        Router* router();
    public:
        DataSourceController();
        ~DataSourceController();
        
        DataSourceControllerDelegate* delegate;
    };
}

#endif /* DataSourceController_hpp */
