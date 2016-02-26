//
//  Utils.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/17/16.
//
//

#ifndef Utils_hpp
#define Utils_hpp

#include "stdafx.h"

internal::BVValue converterValue(rapidjson::Value &value);
internal::BVValueMap converterValueMap(rapidjson::Value &json);
internal::BVValueVector converterValueVector(rapidjson::Value &json);

rapidjson::Document converterToRapidMap(const internal::BVValueMap& map);
rapidjson::Document converterToRapidVector(const internal::BVValueVector& vector);

void mergeObject(rapidjson::Document& target, const internal::BVValueMap& map);

#endif /* Utils_hpp */