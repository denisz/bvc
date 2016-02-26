//
//  Response.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#include "Response.hpp"

using namespace internal::network;
using namespace internal;
using namespace rapidjson;

Response::Response()
: _command("")
, _callbackId("")
, _cacheDocument(nullptr)
, source(Source::UNKNOW) {
    time(&timestamp);
}

Response:: ~Response() {
    if (_cacheDocument) {
        CC_SAFE_DELETE(_cacheDocument);
    }
    
//    CC_SAFE_DELETE_ARRAY(_raw);
}

Response * Response::createWithJSON(const char *json) {
    Response* res = new (std::nothrow)Response();
    if (res->initWithJSON(json)) {
        return res;
    }
    
    CC_SAFE_DELETE(res);
    return res;
}

Response * Response::createWithJSON(const std::string& json) {
    return createWithJSON(json.c_str());
}

Response * Response::createWithDocument(rapidjson::Document *doc)
{
    Response* res = new (std::nothrow)Response();
    if (res->initWithDocument(doc)) {
        return res;
    }
    
    CC_SAFE_DELETE(res);
    return res;
}

Response * Response::createWithoutData() {
    Response* res = new (std::nothrow)Response();
    if (res->initWithoutData()) {
        return res;
    }
    
    CC_SAFE_DELETE(res);
    return res;
}

bool Response::init() {
    if (_cacheDocument != nullptr) {
        _command        = getStringByPointerWithDefault("/command", "unknow");
        _callbackId     = getStringByPointerWithDefault("/" + kKeyCallbackID, "");
        return true;
    }

    return false;
}

bool Response::initWithJSON(const char* json) {
    auto doc = Coder::decode(json);
    if (doc != nullptr) {
        _rawJSON = json;
        return initWithDocument(doc);
    }
    return false;
}

bool Response::initWithDocument(rapidjson::Document* doc) {
    _cacheDocument = doc;
    return init();
}

bool Response::initWithoutData() {
    return initWithJSON("{}");
}

const std::string Response::getStringByPointerWithDefault(const std::string& path, const std::string& def) {
    const rapidjson::Value& value = GetValueByPointerWithDefault(*_cacheDocument, Pointer(path.c_str()), def.c_str());
    return value.GetString();
}

const int Response::getNumberByPointerWithDefault(const std::string& path, const int def) {
    const rapidjson::Value& value = GetValueByPointerWithDefault(*_cacheDocument, Pointer(path.c_str()), def);
    return value.GetInt();
}

const bool Response::getBoolByPointerWithDefault(const std::string &path, const bool def) {
    const rapidjson::Value& value = GetValueByPointerWithDefault(*_cacheDocument, Pointer(path.c_str()), def);
    return value.GetBool();
}

BVValueVector Response::getVectorByPointer(const std::string &path) {
    auto map = GetValueByPointer(*_cacheDocument, Pointer(path.c_str()));
    if (map != nullptr) {
        return converterValueVector(*map);
    }
    
    return BVValueVector();
}

BVValueMap Response::getMapByPointer(const std::string &path) {
    auto map = GetValueByPointer(*_cacheDocument, Pointer(path.c_str()));
    
    if (map != nullptr) {
        return converterValueMap(*map);
    }
    
    return BVValueMap();
}


bool Response::isAnswer() {
    return !_callbackId.empty();
}

rapidjson::Document* Response::document() {
    return _cacheDocument;
}

const std::string Response::command() {
    return _command;
}

const std::string Response::rawText() {
    auto json = Coder::encode(*_cacheDocument);
    return json;
}

const std::string Response::description() {
    std::stringstream ss;
    ss << "Response: [ " << _command << " ] " << rawText() << std::endl;
    return ss.str();
}

const std::string Response::callbackId() {
    return _callbackId;
}
