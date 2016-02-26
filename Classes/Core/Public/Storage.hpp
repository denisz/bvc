//
//  Storage.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef Storage_hpp
#define Storage_hpp

#include "stdafx.h"
#include "cocos2d.h"

namespace common {
    class Storage: public internal::AIRef {
    private:
        cocos2d::UserDefault* _worker;
    public:
        /**
         * Get bool value by key, if the key doesn't exist, will return false.
         * You can set the default value, or it is false.
         * @param key The key to get value.
         * @return Bool value by `key`.
         * @js NA
         */
        bool    getBoolForKey(const char* key);
        
        /**
         * Get bool value by key, if the key doesn't exist, will return passed default value.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @js NA
         */
        virtual bool getBoolForKey(const char* key, bool defaultValue);
        
        /**
         * Get integer value by key, if the key doesn't exist, will return 0.
         * You can set the default value, or it is 0.
         * @param key The key to get value.
         * @return Integer value of the key.
         * @js NA
         */
        int     getIntegerForKey(const char* key);
        
        /**
         * Get bool value by key, if the key doesn't exist, will return passed default value.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @return Integer value of the key.
         * @js NA
         */
        virtual int getIntegerForKey(const char* key, int defaultValue);
        
        /**
         * Get float value by key, if the key doesn't exist, will return 0.0.
         * @param key The key to get value.
         * @return Float value of the key.
         * @js NA
         */
        float    getFloatForKey(const char* key);
        
        /**
         * Get float value by key, if the key doesn't exist, will return passed default value.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @return Float value of the key.
         * @js NA
         */
        virtual float getFloatForKey(const char* key, float defaultValue);
        
        /**
         * Get double value by key, if the key doesn't exist, will return 0.0.
         * @param key The key to get value.
         * @return Double value of the key.
         * @js NA
         */
        double  getDoubleForKey(const char* key);
        
        /**
         * Get double value by key, if the key doesn't exist, will return passed default value.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @return Double value of the key.
         * @js NA
         */
        virtual double getDoubleForKey(const char* key, double defaultValue);
        
        /**
         * Get string value by key, if the key doesn't exist, will return an empty string.
         * @param key The key to get value.
         * @return String value of the key.
         * @js NA
         */
        std::string getStringForKey(const char* key);
        
        /**
         * Get string value by key, if the key doesn't exist, will return passed default value.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @return String value of the key.
         * @js NA
         */
        virtual std::string getStringForKey(const char* key, const std::string & defaultValue);
        
        /**
         * Get Data value by key, if the key doesn't exist, will return an empty Data.
         * @param key The key to get value.
         * @return Data value of the key.
         * @js NA
         */
        cocos2d::Data getDataForKey(const char* key);
        
        /**
         * Get Data value by key, if the key doesn't exist, will return an empty Data.
         * @param key The key to get value.
         * @param defaultValue The default value to return if the key doesn't exist.
         * @return Data value of the key.
         * @js NA
         */
        virtual cocos2d::Data getDataForKey(const char* key, const cocos2d::Data& defaultValue);
        
        // set value methods
        
        /**
         * Set bool value by key.
         * @param key The key to set.
         * @param value A bool value to set to the key.
         * @js NA
         */
        virtual void setBoolForKey(const char* key, bool value);
        /**
         * Set integer value by key.
         * @param key The key to set.
         * @param value A integer value to set to the key.
         * @js NA
         */
        virtual void setIntegerForKey(const char* key, int value);
        /**
         * Set float value by key.
         * @param key The key to set.
         * @param value A float value to set to the key.
         * @js NA
         */
        virtual void setFloatForKey(const char* key, float value);
        /**
         * Set double value by key.
         * @param key The key to set.
         * @param value A double value to set to the key.
         * @js NA
         */
        virtual void setDoubleForKey(const char* key, double value);
        /**
         * Set string value by key.
         * @param key The key to set.
         * @param value A string value to set to the key.
         * @js NA
         */
        virtual void setStringForKey(const char* key, const std::string & value);
        /**
         * Set Data value by key.
         * @param key The key to set.
         * @param value A Data value to set to the key.
         * @js NA
         */
        virtual void setDataForKey(const char* key, const cocos2d::Data& value);
        /**
         * You should invoke this function to save values set by setXXXForKey().
         * @js NA
         */
        virtual void flush();
        
        /**
         * delete any value by key,
         * @param key The key to delete value.
         * @js NA
         */
        virtual void deleteValueForKey(const char* key);
        
        bool init();
        BV_CREATE_FUNC(Storage);
    };
}


#endif /* Storage_hpp */
