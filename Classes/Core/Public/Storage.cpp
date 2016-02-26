//
//  Storage.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "Storage.hpp"

using namespace common;

bool Storage::init() {
    _worker = cocos2d::UserDefault::getInstance();
    return true;
}
bool    Storage::getBoolForKey(const char* key) {
    return _worker->getBoolForKey(key);
}
bool    Storage::getBoolForKey(const char* key, bool defaultValue) {
    return _worker->getBoolForKey(key, defaultValue);
}
int     Storage::getIntegerForKey(const char* key) {
    return _worker->getIntegerForKey(key);
}
int     Storage::getIntegerForKey(const char* key, int defaultValue) {
    return _worker->getIntegerForKey(key, defaultValue);
}
float   Storage::getFloatForKey(const char* key) {
    return _worker->getFloatForKey(key);
}
float   Storage::getFloatForKey(const char* key, float defaultValue) {
    return _worker->getFloatForKey(key, defaultValue);
}
double  Storage::getDoubleForKey(const char* key) {
    return _worker->getDoubleForKey(key);
}
double  Storage::getDoubleForKey(const char* key, double defaultValue) {
    return _worker->getDoubleForKey(key, defaultValue);
}
std::string Storage::getStringForKey(const char* key) {
    return _worker->getStringForKey(key);
}
std::string Storage::getStringForKey(const char* key, const std::string & defaultValue) {
    return _worker->getStringForKey(key, defaultValue);
}
cocos2d::Data Storage::getDataForKey(const char* key) {
    return _worker->getDataForKey(key);
}
cocos2d::Data Storage::getDataForKey(const char* key, const cocos2d::Data& defaultValue) {
    return _worker->getDataForKey(key, defaultValue);
}
void Storage::setBoolForKey(const char* key, bool value) {
    _worker->setBoolForKey(key, value);
}
void Storage::setIntegerForKey(const char* key, int value) {
    _worker->setIntegerForKey(key, value);
}
void Storage::setFloatForKey(const char* key, float value) {
    _worker->setFloatForKey(key, value);
}
void Storage::setDoubleForKey(const char* key, double value) {
    _worker->setDoubleForKey(key, value);
}
void Storage::setStringForKey(const char* key, const std::string & value) {
    _worker->setStringForKey(key, value);
}
void Storage::setDataForKey(const char* key, const cocos2d::Data& value) {
    _worker->setDataForKey(key, value);
}
void Storage::flush(){
    _worker->flush();
}
void Storage::deleteValueForKey(const char* key) {
    _worker->deleteValueForKey(key);
}