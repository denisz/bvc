//
//  RequestCommand.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef RequestCommand_hpp
#define RequestCommand_hpp

#include "stdafx.h"
#include "Request.hpp"
#include "md5.h"
#include "Utils.hpp"

namespace common {
    class RequestCommand: public internal::AIRef {
    public:
        static const std::string kDefaultPinName;
    private:
        std::string _command;
        std::string _callbackId;
        bool _checkPinningEnabled;
        std::string _localDatastorePinName;
        rapidjson::Document _params;
        RequestCommand();
    public:
        ~RequestCommand();
        int cachePolicy = kCachePolicyIgnoreCache;
        
        void fromLocalDatastore();
        std::string fromPin();
        bool checkPinningEnabled();
        void fromPinWithName(const std::string& name);
        
        const std::string hash();
        void setCallbackId(const std::string& callbackId);
        bool initWithCommand(const std::string& command);
        const std::string callbackId();
        internal::network::Request request();
        
        
        void setValue(const std::string& path, const char* value);
        void setValue(const std::string& path, const std::string& value);
        void setValue(const std::string& path, const int value);
        void setValue(const internal::BVValueMap& map);
        void setValue(const std::string& path, const internal::BVValueMap& map);
        void setValue(const std::string& path, const internal::BVValueVector& vector);
        void setValue(const std::string& path, bool value);
        
        static RequestCommand* createWithCommand(const std::string& command);
    };
}

#endif /* RequestCommand_hpp */
