//
//  Response.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef Response_hpp
#define Response_hpp

#include "stdafx.h"
#include "Coder.hpp"
#include "Utils.hpp"

namespace internal {
    namespace network {
        class Response: public internal::AIRef {
        public:
            enum class Source {UNKNOW, LOCALE, NETWORKCLIENT};
        private:
            rapidjson::Document* _cacheDocument;
            std::string _command;
            std::string _callbackId;
            const char* _rawJSON;
            bool init();
            bool initWithoutData();
            bool initWithJSON(const char *json);
            bool initWithDocument(rapidjson::Document* doc);
            Response();
        public:
            ~Response();
            time_t timestamp;
            Source source;
            const std::string rawText();
            rapidjson::Document* document();
            const std::string command();
            const std::string callbackId();
            bool isAnswer();
            
            const std::string getStringByPointerWithDefault(const std::string &path,const std::string &def);
            const int getNumberByPointerWithDefault(const std::string &path, const int def);
            const bool getBoolByPointerWithDefault(const std::string &path, const bool def);
            
            internal::BVValueVector getVectorByPointer(const std::string &path);
            internal::BVValue       getVectorByPointerAsValue(const std::string &path);
            internal::BVValueMap    getMapByPointer(const std::string &path);
            internal::BVValueMap    getMapByPointer(const std::string &path, const BVValueMap& def);
            internal::BVValue       getMapByPointerAsValue(const std::string &path);
            
            static Response * createWithJSON(const std::string& json);
            static Response* createWithJSON(const char *json);
            static Response* createWithDocument(rapidjson::Document *doc);
            static Response* createWithoutData();
            
            const std::string description();
        };
    }
}
#endif /* Response_hpp */
