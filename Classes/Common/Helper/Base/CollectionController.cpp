//
//  CollectionController.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/10/16.
//
//

#include "CollectionController.hpp"

using namespace game;

const std::string kCollectionKey = "id";

bool compareBVValueMapById(BVValue& model1, BVValue& model2) {
    auto type1 = model1.getType();
    auto type2 = model2.getType();
    
    if (type1 == type2  && type1 == BVValue::Type::MAP) {
        auto map1 = model1.asValueMap();
        auto map2 = model2.asValueMap();
        
        return map1[kCollectionKey] == map2[kCollectionKey];
    }
    
    return false;
}

CollectionController::CollectionController() {
    _objects = BVValueVector();
}

CollectionController::~CollectionController() {
    clear();
}

bool CollectionController::init() {
    if (DataSourceController::init()) {
        setupEndPoints();
        return true;
    }
    
    return false;
}

CollectionController* CollectionController::endPoint(Type type, const std::string& cmd, Parse parse) {
    
   router()
        ->command(cmd, CC_CALLBACK_1(CollectionController::serve, this, parse, type));
    

    return this;
}

bool CollectionController::serve(internal::network::Response* res, Parse parse, Type type) {
    auto model = parse(res);
    
    if (!model.isNull()) {
        switch (type) {
            case Type::INSERT:
                insertModel(model);
                break;
            case Type::DELETE:
                removeModel(model);
                break;
            case Type::UPDATE:
                updateModel(model);
                break;
            case Type::RELOAD:
                reloadModels(model);
                break;
        }
    }
    
    return true;
}

RequestCommand* CollectionController::commandForReloadData() {
    return nullptr;
}

void CollectionController::reloadData() {
    auto cmd = commandForReloadData();
    CC_SAFE_DEFRREDRELEASE(cmd);
    
    if (cmd != nullptr) {
        runCommandInBackground(*cmd);
    }
}

void CollectionController::insertModel(BVValue& obj) {
    if (delegate != nullptr)
        delegate->willChange(this, DataSourceControllerOptions::INSERT, obj);
    
    auto type = obj.getType();
    
    if (type == BVValue::Type::VECTOR) {
        auto vector = obj.asValueVector();
        _objects.insert(_objects.end(), vector.begin(), vector.end());
    } else {
        _objects.push_back(obj);
    }
    
    if (delegate != nullptr)
        delegate->didChange(this, DataSourceControllerOptions::INSERT, obj);
}

void CollectionController::removeModel(BVValue& obj) {
    if (delegate != nullptr)
        delegate->willChange(this, DataSourceControllerOptions::DELETE, obj);
    
    auto type = obj.getType();
    
    if (type == BVValue::Type::VECTOR) {
        auto vector = obj.asValueVector();
        
        for (auto item: vector)
            removeModel(item);
    } else {
        auto pred = std::bind(compareBVValueMapById, obj, std::placeholders::_1);
        auto it = std::find_if(_objects.begin(), _objects.end(), pred);
        if (it != _objects.end())
            _objects.erase(it);
    }
    
    if (delegate != nullptr)
        delegate->didChange(this, DataSourceControllerOptions::DELETE, obj);
}

void CollectionController::updateModel(BVValue& obj) {
    if (delegate != nullptr)
        delegate->willChange(this, DataSourceControllerOptions::UPDATE, obj);
    
    auto type = obj.getType();

    if (type == BVValue::Type::VECTOR) {
        auto vector = obj.asValueVector();
        for (auto item: vector)
            updateModel(item);
    } else {
        auto pred = std::bind(compareBVValueMapById, obj, std::placeholders::_1);
        auto it = std::find_if(_objects.begin(), _objects.end(), pred);
        if (it != _objects.end())
            *it = obj;
    }
    
    if (delegate != nullptr)
        delegate->didChange(this, DataSourceControllerOptions::UPDATE, obj);
}

void CollectionController::reloadModels(BVValue& obj) {
    if (delegate != nullptr)
        delegate->willChange(this, DataSourceControllerOptions::RELOAD, obj);
    
    clear();
    
    auto type = obj.getType();
    
    if (type == BVValue::Type::VECTOR) {
        auto vector = obj.asValueVector();
        _objects.insert(_objects.end(), vector.begin(), vector.end());
    } else {
        _objects.push_back(obj);
    }
    
    if (delegate != nullptr)
        delegate->didChange(this, DataSourceControllerOptions::RELOAD, obj);
}

BVValue* CollectionController::findModelById(int objectId) {
    auto map = BVValueMap();
    map[kCollectionKey] = objectId;
    auto obj = BVValue(map);
    
    return findModelById(obj);
}

BVValue* CollectionController::findModelById(const std::string &objectId) {
    auto map = BVValueMap();
    map[kCollectionKey] = objectId;
    auto obj = BVValue(map);
    
    return findModelById(obj);
}


BVValue* CollectionController::findModelById(BVValue& obj) {
    auto pred = std::bind(compareBVValueMapById, obj, std::placeholders::_1);
    auto it = std::find_if(_objects.begin(), _objects.end(), pred);
    if (it != _objects.end()) {
        return &*it;
    }
    return nullptr;
}

bool CollectionController::containsModelById(int objectId) {
    auto model = findModelById(objectId);
    return model != nullptr;
}

bool CollectionController::containsModelById(const std::string &objectId) {
    auto model = findModelById(objectId);
    return model != nullptr;
}

int CollectionController::count() {
    return _objects.size();
}

void CollectionController::clear() {
    _objects.clear();
}

BVValue* CollectionController::getModelByIndex(ssize_t idx) {
    if (idx >= 0 && idx < _objects.size()) {
        return &_objects[idx];
    }
    
    return nullptr;
}


