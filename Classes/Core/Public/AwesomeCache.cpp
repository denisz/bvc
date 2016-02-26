//
//  AwesomeCache.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/19/16.
//
//

#include "AwesomeCache.hpp"

using namespace common;
using namespace internal::network;

AwesomeCache::AwesomeCache() {
    FileUtils::sharedInstance()->createDirectory(kCacheDirPath);
}

void AwesomeCache::saveInBackgroundWithName(const std::string &name, Response *res) {
    auto filename   = generateFileName(name);
    auto data       = internal::BVValueMap();
    auto text       = res->rawText();
    auto timestamp  = std::to_string(res->timestamp);
    
    if (!text.empty()) {
        data[kCacheRawDataKey]   = text;
        data[kCacheTimestampKey] = timestamp;
        data[kCacheVersionKey]   = kAppVersion;
        FileUtils::sharedInstance()->writeContentToFile(data, filename);
    }
}

void AwesomeCache::removeInBackgroundWithName(const std::string &name) {
    auto filename   = generateFileName(name);
    FileUtils::sharedInstance()->removeFile(filename);
}

bool AwesomeCache::existsCache(const std::string &name) {
    auto filename = generateFileName(name);
    return FileUtils::sharedInstance()->isFileExist(filename);
}

Response* AwesomeCache::loadInBackgroundWithName(const std::string &name) {
    auto filename = generateFileName(name);
    auto data = FileUtils::sharedInstance()->readContentFromFile(filename);
    auto raw = data[kCacheRawDataKey].asString();
    
    if (!raw.empty()) {
        //проверить число
        auto res = Response::createWithJSON(raw);
        res->source = Response::Source::LOCALE;
        return res;
    }
    
    return  nullptr;
}

void AwesomeCache::purge() {
    FileUtils::sharedInstance()->purgeWithPrefix(kCacheDirPath);
}

std::string AwesomeCache::generateFileName(const std::string& hash) {
    return fmt::format("{0}{1}.xml", kCacheDirPath, hash);
}

AwesomeCache* AwesomeCache::create() {
    auto ref = new AwesomeCache();
    return ref;
}