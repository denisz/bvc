//
//  Coder.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "Coder.hpp"

using namespace internal;
using namespace rapidjson;

const std::string Coder::encode(rapidjson::Document &doc) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    return buffer.GetString();
}

rapidjson::Document* Coder::decode(const char* json) {
    rapidjson::Document* doc = new rapidjson::Document();
    
    if (doc->Parse(json).HasParseError() == false) {
        return doc;
    } else {
        std::cout << "JSON Parse error: " << doc->GetParseError() << std::endl;
        delete doc;
    }
    
    return nullptr;
}
