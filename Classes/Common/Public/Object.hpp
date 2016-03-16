//
//  Object.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/17/16.
//
//

#ifndef Object_hpp
#define Object_hpp

#include "stdafx.h"
#include "Plugins.hpp"
#include "Utils.hpp"

using namespace internal;

namespace game {
    class Object: public internal::AIRef {
    protected:
        std::string _objectIdKey = "id";
        std::string _classname;
        BVValueMap* _serverData;
        std::string _objectId;
        virtual bool init(const std::string& classname = "", const std::string& objectId = "");
        Object();
        std::mutex _mutex;
    public:
        ~Object();
        bool containsKey(const std::string &key) const;
        const std::string objectId() const;
        
        const BVValue valueForKey(const std::string &key, const int defVal) const;
        const BVValue valueForKey(const std::string &key, const std::string &defVal) const;
        const BVValue valueForKey(const std::string &key, const BVValue &defVal = BVValue::Null) const;
        
        void setObject(BVValue &value, const std::string &key);
        void setObject(BVValueMap &value, const std::string &key);
        void setObject(BVValueVector &value, const std::string &key);
        
        void clear();
        void mergeFromServer(BVValueMap &newData,  bool clear = false);
        
        BVValueMap* data();
        
        const std::string hash() const;

        bool operator== (const Object& v);
        
        static Object* createWithName(const std::string& classname);
    };
}

#endif /* Object_hpp */
