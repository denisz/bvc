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

Object* Object::createWithName(const std::string &classname) {
    auto obj = new Object();
    if (obj->init(classname)) {
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return obj;
}

void Object::mergeFromServer(BVValueMap &newData, bool clear) {
    if (clear) {
        this->clear();
    }
    
    for(auto& it : newData) {
        setObject(it.second, it.first);
    }
}

const std::string Object::objectId() const {
    return _objectId;
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

void Object::setObject(BVValue &value, const std::string &key) {
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (_serverData != nullptr) {
        (*_serverData)[key] = value;
        
        if (key == _objectIdKey) {
            _objectId = value.asString();
        }
    }
}

BVValueMap* Object::data() {
    return _serverData;
}

void Object::setObject(BVValueMap &value, const std::string &key) {
    auto map = BVValue(value);
    return setObject(map, key);
}

void Object::setObject(BVValueVector &value, const std::string &key) {
    auto vector = BVValue(value);
    return setObject(vector, key);
}

const std::string Object::hash() const {
    return this->_classname + this->objectId();
}

bool Object::operator== (const Object &v) {
    return this->hash() == v.hash();
}