//
//  Utils.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/17/16.
//
//

#include "Utils.hpp"

using namespace internal;
using namespace rapidjson;

BVValueVector converterValueVector(Value &json) {
    auto vector = BVValueVector();
    
    if (json.IsArray()) {
        for (auto itr = json.Begin(); itr != json.End(); ++itr) {
            //replace .emplace()
            vector.push_back(converterValue(*itr));
        }
    }
    
    return vector;
}

BVValueMap converterValueMap(Value &json) {
    auto map = BVValueMap();
    
    if (json.IsObject()) {
        for (auto itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
        {
            auto key = itr->name.GetString();
            map[key] = converterValue(itr->value);
        }
    }
    return map;
}

BVValue converterValue(Value &value) {
    auto type = value.GetType();
    
    if (type == Type::kStringType) {
        return BVValue(value.GetString());
    } else if (type == Type::kNumberType) {
        return BVValue(value.GetDouble());//исправить на int
    } else if (type == Type::kFalseType || type == Type::kTrueType) {
        return BVValue(value.GetBool());
    } else if (type == Type::kObjectType) {
        return  BVValue(converterValueMap(value));
    } else if (type == Type::kArrayType) {
        return  BVValue(converterValueVector(value));
    } else {
        return BVValue::Null;
    }
}

rapidjson::Document converterToRapidMap(const BVValueMap& map) {
    auto doc = rapidjson::Document();
    mergeObject(doc, map);
    return doc;
}

rapidjson::Document converterToRapidVector(const BVValueVector& vector) {
    auto doc = Document();
    doc.Parse("[]");
    
    auto key_a = Pointer("/-");
    
    for (auto it = vector.begin() ; it != vector.end(); ++it) {
        auto value = *it;
        auto type  = value.getType();
        
        if (type == BVValue::Type::INTEGER) {
            SetValueByPointer(doc, key_a, value.asInt());
        } else if (type == BVValue::Type::STRING) {
            SetValueByPointer(doc, key_a, value.asString().c_str());
        } else if (type == BVValue::Type::BOOLEAN) {
            SetValueByPointer(doc, key_a, value.asBool());
        } else if (type == BVValue::Type::FLOAT) {
            SetValueByPointer(doc, key_a, value.asFloat());
        } else if (type == BVValue::Type::DOUBLE) {
            SetValueByPointer(doc, key_a, value.asDouble());
        } else if (type == BVValue::Type::MAP) {
            SetValueByPointer(doc, key_a, converterToRapidMap(value.asValueMap()));
        } else if (type == BVValue::Type::VECTOR) {
            SetValueByPointer(doc, key_a, converterToRapidVector(value.asValueVector()));
        }
    }
    
    return doc;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void mergeObject(rapidjson::Document& target, const BVValueMap& map) {
    for (auto &item: map) {
        auto key    = Pointer(("/" + item.first).c_str());
        auto value  = item.second;
        auto type   = value.getType();
        
        if (type == BVValue::Type::INTEGER) {
            SetValueByPointer(target, key, value.asInt());
        } else if (type == BVValue::Type::STRING) {
            SetValueByPointer(target, key, value.asString().c_str());
        } else if (type == BVValue::Type::BOOLEAN) {
            SetValueByPointer(target, key, value.asBool());
        } else if (type == BVValue::Type::FLOAT) {
            SetValueByPointer(target, key, value.asFloat());
        } else if (type == BVValue::Type::DOUBLE) {
            SetValueByPointer(target, key, value.asDouble());
        } else if (type == BVValue::Type::MAP) {
            SetValueByPointer(target, key, converterToRapidMap(value.asValueMap()));
        } else if (type == BVValue::Type::VECTOR) {
            SetValueByPointer(target, key, converterToRapidVector(value.asValueVector()));
        }
    }
}


void mergeObject(rapidjson::Value& target, rapidjson::Value& source, rapidjson::Value::AllocatorType& allocator) {
    for (auto itr = source.MemberBegin(); itr != source.MemberEnd(); ++itr)
        target.AddMember(itr->name, itr->value, allocator);
}

void extendBVValueMap(BVValueMap& destination, const BVValueMap& source) {
    for (auto& item: source) {
        destination[item.first] = item.second;
    }
}

void extendBVValue(BVValue& destination, const BVValueMap& source) {
    auto typeDestination    = destination.getType();
    if (typeDestination == BVValue::Type::MAP) {
        extendBVValueMap(destination.asValueMap(), source);
    }
}

void extendBVValue(BVValue& destination, const BVValue& source) {
    auto typeDestination    = destination.getType();
    auto typeSource         = source.getType();
    
    if (typeDestination == typeSource && typeSource == BVValue::Type::MAP) {
        extendBVValueMap(destination.asValueMap(), source.asValueMap());
    }
}


std::string now() {
    time_t timestamp;
    time(&timestamp);
    return std::to_string(timestamp);
}