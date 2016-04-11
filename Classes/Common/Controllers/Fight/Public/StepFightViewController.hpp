//
//  StepFightViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/25/16.
//
//

#ifndef StepFightViewController_hpp
#define StepFightViewController_hpp

#include "stdafx.h"
#include "GameViewController.hpp"
#include "ContextFight.hpp"

#define BV_CREATE_FUNC_WITH_FIGHT_CONTEXT(__TYPE__) \
static __TYPE__* createWithFightContext(ContextFight* context) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->initWithContextFight(context)) \
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

namespace game {
    class StepFightViewController: public GameViewController, public ContextFightEvents {
    private:
        ContextFight* _contextFight;
    public:
        StepFightViewController();
        ~StepFightViewController();
        void subscribeContext();
        void unsubscribeContext();
        ContextFight* context();
        bool initWithContextFight(ContextFight* context);
    };
}

#endif /* StepFightViewController_hpp */
