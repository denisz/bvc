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

USING_NS_CC;

using namespace std;

class Localized {
    typedef map<string, string> StringStringMap;
private:
    virtual ~Localized();
    Localized();
public:
    static string getString(const string &key);
    static void purge();
    static void load();
    
    static string languageShortNameForType(LanguageType type);
    static bool isLanguageSupported(LanguageType language);
private:
    StringStringMap strings;
    static Localized *__sharedInstance;
};

#endif /* Localized_hpp */
