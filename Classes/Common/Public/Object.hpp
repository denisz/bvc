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
        virtual bool init(const std::string& classname = "Object", const std::string& objectId = "");
        virtual bool initWithData(const std::string& classname, BVValueMap &newData);
        Object();
        std::mutex _mutex;
    public:
        ~Object();
        
        const std::string hash() const;
        const int objectIdAsInt() const;
        const std::string objectId() const;
        bool containsKey(const std::string &key) const;
        
        const BVValue valueForKey(const std::string &key, const int defVal) const;
        const BVValue valueForKey(const std::string &key, const std::string &defVal) const;
        const BVValue valueForKey(const std::string &key, const BVValue &defVal = BVValue::Null) const;
        
        void setObject(const BVValue &value, const std::string &key);
        void setObject(const BVValueMap &value, const std::string &key);
        void setObject(const BVValueVector &value, const std::string &key);
        
        void clear();
        void mergeFromServer(const BVValue &newData,  bool clear = false);
        void mergeFromServer(const BVValueMap &newData,  bool clear = false);
        
        BVValueMap* data();

        bool operator== (const Object& v);
        
        static Object* createWithName(const std::string& classname);
        static Object* createWithNameAndData(const std::string& classname, BVValueMap &newData);
    };
}

#endif /* Object_hpp */
