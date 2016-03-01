//
//  Localized.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "Localized.hpp"

Localized *Localized::__sharedInstance = nullptr;

static cocos2d::LanguageType AvailableLanguages[] = {
    cocos2d::LanguageType::ENGLISH,
    cocos2d::LanguageType::RUSSIAN
};

Localized::~Localized() {
    //
}

Localized::Localized() {
    //
}

void Localized::load() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new Localized();
    } else {
        return;
    }
    
    unsigned char *t = nullptr;
    ssize_t stringsDataSize = 0;
    t = (cocos2d::FileUtils::getInstance()->getFileData("strings.json", "r", &stringsDataSize));
    
    char *stringsData = new char[stringsDataSize + 1];
    memcpy(stringsData, t, stringsDataSize);
    stringsData[stringsDataSize] = NULL;
    
    delete[] t;
    t = NULL;
    
    rapidjson::Document stringsDoc;
    stringsDoc.Parse<0>(stringsData);
    
    const auto &stringsMap = stringsDoc["strings"];
    if(stringsMap.IsObject()) {
        for(auto it = stringsMap.MemberBegin(); it != stringsMap.MemberEnd(); ++it) {
            auto key = it->name.GetString();
            auto value = it->value.GetString();
            
            __sharedInstance->strings.insert(std::make_pair(key, value));
        }
    }
    
    delete[] stringsData;
}

void Localized::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;
}

std::string Localized::getString(const std::string &key) {
    if(__sharedInstance == nullptr) {
        Localized::load();
    }
    
    auto stringIt = __sharedInstance->strings.find(key);
    
    if(stringIt != __sharedInstance->strings.end()) {
        return stringIt->second;
    } else {
        CCLOG("String not found for key: %s", key.c_str());
    }
    
    return kLocalizedStringNotFound;
}

bool Localized::isLanguageSupported(cocos2d::LanguageType language) {
    for(cocos2d::LanguageType l: AvailableLanguages) {
        if(l == language) {
            return true;
        }
    }
    
    return false;
}

std::string Localized::languageShortNameForType(cocos2d::LanguageType type) {
    auto languagePrefix = "en";
    switch(type) {
        case cocos2d::LanguageType::ENGLISH:
            languagePrefix = "en"; break;
            //        case LanguageType::CHINESE:
            //            languagePrefix = "zh"; break;
            //        case LanguageType::FRENCH:
            //            languagePrefix = "fr"; break;
            //        case LanguageType::ITALIAN:
            //            languagePrefix = "it"; break;
            //        case LanguageType::GERMAN:
            //            languagePrefix = "de"; break;
            //        case LanguageType::SPANISH:
            //            languagePrefix = "es"; break;
        case cocos2d::LanguageType::RUSSIAN:
            languagePrefix = "ru"; break;
            //        case LanguageType::KOREAN:
            //            languagePrefix = "ko"; break;
            //        case LanguageType::JAPANESE:
            //            languagePrefix = "ja"; break;
            //        case LanguageType::HUNGARIAN:
            //            languagePrefix = "hu"; break;
            //        case LanguageType::PORTUGUESE:
            //            languagePrefix = "pt"; break;
            //        case LanguageType::ARABIC:
            //            languagePrefix = "ar"; break;
            //        case LanguageType::NORWEGIAN:
            //            languagePrefix = "nb"; break;
            //        case LanguageType::POLISH:
            //            languagePrefix = "pl"; break;
        default:
            break;
    }
    
    return languagePrefix;
}