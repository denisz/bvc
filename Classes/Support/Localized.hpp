//
//  Localized.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#ifndef Localized_hpp
#define Localized_hpp

#include "stdafx.h"
#include <map>
#include <string>
#include "cocos2d.h"

#define kLocalizedStringNotFound "notFound"

class Localized {
    typedef std::map<std::string, std::string> StringStringMap;
private:
    virtual ~Localized();
    Localized();
public:
    static std::string getString(const std::string &key);
    static void purge();
    static void load();
    
    static std::string languageShortNameForType(cocos2d::LanguageType type);
    static bool isLanguageSupported(cocos2d::LanguageType language);
private:
    StringStringMap strings;
    static Localized *__sharedInstance;
};

#endif /* Localized_hpp */
