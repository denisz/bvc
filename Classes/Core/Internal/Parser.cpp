//
//  Parser.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#include "Parser.hpp"

using namespace internal::network;

Parser::Parser() {
    buffer = new char[0];
}

Parser::~Parser() {
    clearBuffer();
}

void Parser::clearBuffer() {
    delete[] buffer;
    buffer = new char[0];
}

rapidjson::Document* Parser::parse(const char *json) {
//    strcat (buffer, json);
    auto doc = Coder::decode(json);
    
    if (doc != nullptr) {
//        clearBuffer();
        return doc;
    }
    
    return nullptr;
}