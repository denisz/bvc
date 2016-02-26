//
//  AwesomeCache.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/19/16.
//
//

#ifndef AwesomeCache_hpp
#define AwesomeCache_hpp

#include "stdafx.h"
#include "Response.hpp"
#include "FileUtils.hpp"

namespace common {
    class AwesomeCache {
        const std::string kCacheRawDataKey      = "raw";
        const std::string kCacheTimestampKey    = "timestamp";
        const std::string kCacheVersionKey      = "version";
    private:
        std::string generateFileName(const std::string& hash);
        AwesomeCache();
    public:
        void saveInBackgroundWithName(const std::string &name, internal::network::Response *res);
        void removeInBackgroundWithName(const std::string &name);
        bool existsCache(const std::string &name);
        internal::network::Response* loadInBackgroundWithName(const std::string &name);
        void purge();
        
        static AwesomeCache* create();
    };
}

#endif /* AwesomeCache_hpp */
