//
//  RequestCommand.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "RequestCommand.hpp"


using namespace common;
using namespace internal::network;
using namespace internal;
using namespace rapidjson;

const std::string callbackKey() {
    return fmt::format("/{0}", kKeyCallbackID);
}

const std::string RequestCommand::kDefaultPinName= "___default___";

RequestCommand::RequestCommand()
: _command("")
, _params(Document())
, _callbackId("")
, _localDatastorePinName(kDefaultPinName)
, _checkPinningEnabled(false) {
    _params.SetObject();
}

bool RequestCommand::initWithCommand(const std::string& command) {
    _command = command;
    return true;
}

RequestCommand* RequestCommand::createWithCommand(const std::string& command) {
    RequestCommand* cmd = new RequestCommand();
    if (cmd->initWithCommand(command)) {
        return cmd;
    }
    
    CC_SAFE_DELETE(cmd);
    return nullptr;
}

RequestCommand::~RequestCommand() {
}

Request RequestCommand::request() {
    auto req = Request();
    
    SetValueByPointer(req.out, "/command", _command.c_str());
    SetValueByPointer(req.out, "/params",  Value(_params, req.out.GetAllocator()));
    
    if (!_callbackId.empty()) {
        SetValueByPointer(req.out, Pointer(callbackKey().c_str()), _callbackId.c_str());
    }
    
    return req;
}

void RequestCommand::fromLocalDatastore() {
    cachePolicy = kCachePolicyCacheElseNetwork;
}

void RequestCommand::fromPinWithName(const std::string& name) {
    cachePolicy = kCachePolicyCacheElseNetwork;
    _checkPinningEnabled    = true;
    _localDatastorePinName  = name;
}

bool RequestCommand::checkPinningEnabled() {
    return _checkPinningEnabled;
}

std::string RequestCommand::fromPin() {
    return _localDatastorePinName;
}

void RequestCommand::setValue(const std::string& path, const std::string& value) {
    SetValueByPointer(_params, Pointer(path.c_str()), value.c_str());
}

void RequestCommand::setValue(const std::string& path, bool value) {
    SetValueByPointer(_params, Pointer(path.c_str()), value);
}

void RequestCommand::setValue(const std::string& path, const char* value) {
    SetValueByPointer(_params, Pointer(path.c_str()), value);
}

void RequestCommand::setValue(const std::string& path, const int number) {
    SetValueByPointer(_params, Pointer(path.c_str()), number);
}

void RequestCommand::setValue(const std::string& path, const BVValueMap& map) {
    auto json = converterToRapidMap(map);
    SetValueByPointer(_params, Pointer(path.c_str()), json);
}

void RequestCommand::setValue(const BVValueMap& map) {
    mergeObject(_params, map);
}

void RequestCommand::setValue(const std::string& path, const BVValueVector& vector) {
    auto json = converterToRapidVector(vector);
    SetValueByPointer(_params, Pointer(path.c_str()), json);
}


const std::string RequestCommand::hash() {
    return MD5(_command).toStr();
}

void RequestCommand::setCallbackId(const std::string& callbackId) {
    _callbackId = callbackId;
}

const std::string RequestCommand::callbackId() {
    return _callbackId;
}
