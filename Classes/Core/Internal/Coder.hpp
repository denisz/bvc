//
//  Coder.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef Coder_hpp
#define Coder_hpp

#include "stdafx.h"

namespace internal {
    class Coder {
    private:
    public:
        static const std::string encode(rapidjson::Document &doc);
        static rapidjson::Document* decode(const char* json);
    };
}

#endif /* Coder_hpp */
