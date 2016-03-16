//
//  Parser.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/11/16.
//
//

#ifndef Parser_hpp
#define Parser_hpp

#include "stdafx.h"
#include "Coder.hpp"

namespace internal {
    namespace network {
        class Parser {
        private:
            char *buffer;
            void clearBuffer();
        public:
            Parser();
            ~Parser();
            rapidjson::Document* parse(const char *json);
        };
    }
}

#endif /* Parser_hpp */
