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
        const BVValue valueForKey(const std::string &key, const BVValue &defValue = BVValue::Null) const;
        const BVValue valueForKey(const std::string &key, const std::string &defvalue) const;
        const BVValue valueForKey(const std::string &key, const int defvalue) const;
        void setObject(BVValue &value, const std::string &key);
        void setObject(BVValueMap &value, const std::string &key);
        void setObject(BVValueVector &value, const std::string &key);
        void mergeFromServer(BVValueMap &newData,  bool clear = false);
        void clear();
        
        BVValueMap* data();
        
        const std::string hash() const;
        /** == operator overloading */
        bool operator== (const Object& v);
        
        static Object* createWithName(const std::string& classname);
    };
}

#endif /* Object_hpp */
