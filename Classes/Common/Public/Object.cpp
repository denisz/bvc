//
//  Object.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/17/16.
//
//

#include "Object.hpp"

using namespace internal;
using namespace game;

Object::Object()
: _objectId("")
, _classname("")
, _serverData(nullptr) {
    _serverData = new BVValueMap();
}

Object::~Object() {
    CC_SAFE_DELETE(_serverData);
}

bool Object::init(const std::string &classname, const std::string& objectId) {
    _classname = classname;
    _objectId  = objectId;
    return true;
}

bool Object::initWithData(const std::string& classname, BVValueMap &newData) {
    _classname = classname;
    mergeFromServer(newData);
    return true;
}

Object* Object::createWithNameAndData(const std::string &classname, BVValueMap &newData) {
    auto ref = new Object();
    if (ref->initWithData(classname, newData)) {
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

Object* Object::createWithName(const std::string &classname) {
    auto ref = new Object();
    if (ref->init(classname)) {
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

void Object::mergeFromServer(const BVValueMap &newData, bool clear) {
    if (clear) {
        this->clear();
    }
    
    for(auto& it : newData) {
        setObject(it.second, it.first);
    }
}

void Object::mergeFromServer(const BVValue &newData,  bool clear) {
    if (newData.getType() == BVValue::Type::MAP) {
        return mergeFromServer(newData.asValueMap(), clear);
    }
}

const std::string Object::objectId() const {
    return _objectId;
}

const int Object::objectIdAsInt() const {
    return std::stoi(objectId());
}

bool Object::containsKey(const std::string& key) const {
    auto search = _serverData->find(key);
    return search != _serverData->end();
}

const BVValue Object::valueForKey(const std::string& key, const BVValue &defValue) const {
    if (_serverData != nullptr) {
        auto find = _serverData->find(key);
        
        if (find != _serverData->end()) {
            return find->second;
        }
    }
    
    return defValue;
}

void Object::clear() {
    if (_serverData != nullptr) {
        _serverData->clear();
    }
}

const BVValue Object::valueForKey(const std::string &key, const std::string &defvalue) const {
    return valueForKey(key, BVValue(defvalue));
}

const BVValue Object::valueForKey(const std::string &key, const int defvalue) const {
    return valueForKey(key, BVValue(defvalue));
}

void Object::setObject(const BVValue &value, const std::string &key) {
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (_serverData != nullptr) {
        (*_serverData)[key] = value;
        
        if (key == _objectIdKey) {
            _objectId = std::to_string(value.asInt());
        }
    }
}

BVValueMap* Object::data() {
    return _serverData;
}

void Object::setObject(const BVValueMap &value, const std::string &key) {
    auto map = BVValue(value);
    return setObject(map, key);
}

void Object::setObject(const BVValueVector &value, const std::string &key) {
    auto vector = BVValue(value);
    return setObject(vector, key);
}

const std::string Object::hash() const {
    return this->_classname + this->objectId();
}

bool Object::operator== (const Object &v) {
    return this->hash() == v.hash();
}