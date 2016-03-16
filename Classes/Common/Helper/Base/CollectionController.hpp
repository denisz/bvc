//
//  CollectionController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/10/16.
//
//

#ifndef CollectionController_hpp
#define CollectionController_hpp

#include "stdafx.h"
#include "DataSourceController.hpp"

namespace game {
    class CollectionController: public DataSourceController, public DataSourceViewControllerDelegate {
    public:
        enum class Type {RELOAD, INSERT, UPDATE, DELETE};
        typedef std::function<BVValue(internal::network::Response* res)> Parse;

    private:
        internal::BVValueVector _objects;
        
    private:
        bool serve(internal::network::Response* res, Parse parse, Type type);
        
        void insertModel(BVValue& obj);
        void removeModel(BVValue& obj);
        void updateModel(BVValue& obj);
        void reloadModels(BVValue& obj);
    protected:
        virtual void setupEndPoints() {};
        virtual bool init();
        virtual RequestCommand* commandForReloadData();
    public:
        CollectionController();
        ~CollectionController();
        
//MARK: implementation DataSourceViewControllerDelegate
        int count();
        BVValue* getModelByIndex(ssize_t idx);
        
        void reloadData();
        void clear();
        
        BVValue* findModelById(const std::string &objectId);
        BVValue* findModelById(int objectId);
        BVValue* findModelById(BVValue& obj);
        
        bool containsModelById(const std::string &objectId);
        bool containsModelById(int objectId);
        
        CollectionController* endPoint(Type type, const std::string& cmd, Parse parse);
    };
}

#endif /* CollectionDataSourceController_hpp */
