//
//  Core.h
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef Core_h
#define Core_h

#define BV_CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init()) \
{ \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#define BV_CREATE_FUNC_WITH_SIZE(__TYPE__) \
static __TYPE__* createWithSize(const cocos2d::Size &contentSize) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->initWithSize(contentSize)) \
{ \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init()) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#define BV_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define BV_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define BV_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define BV_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define REGISTER_GETTER_PLUGIN(__TYPE__, name) \
static __TYPE__* _##name;\
static __TYPE__* name () {\
if (Plugins::_##name == nullptr) {\
Plugins::_##name = __TYPE__::create();\
}\
return Plugins::_##name;\
}

#define IM_REGISTER_PLUGIN(__TYPE__, name)\
__TYPE__* Plugins::_##name;


#define CC_ACTION_DEC(name)\
void action##name (internal::network::Response* res);
#define CC_COMMAND_DEC(name)\
void command##name (internal::ActionsClient::Event* event);

//#define CC_ACTION_IMP(__TYPE__, name)\
//void __TYPE__::action##name (internal::network::Response* res);
//#define CC_COMMAND_IMP(__TYPE__, name)\
//void __TYPE__::command##name (internal::ActionsClient::Event* event);


#endif /* Core_h */
