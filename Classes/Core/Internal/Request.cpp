//
//  Request.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#include "Request.hpp"

using namespace internal::network;
using namespace rapidjson;

Request::Request()
: out(Document()){
    time(&timestamp);
}

const std::string Request::outReadyMessage() {
    return Coder::encode(out);
}