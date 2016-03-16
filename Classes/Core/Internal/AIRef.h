//
//  AIRef.h
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef AIRef_h
#define AIRef_h

#define CC_SAFE_DEFRREDRELEASE(p)     internal::DeferredRef __guard(p);
#define CC_SAFE_AUTORELEASE(p)  do { if(p) { (p)->autorelease(); } } while(0)

#include "cocos2d.h"

namespace internal {
    typedef cocos2d::Ref AIRef;
    
    struct DeferredRef{
    private:
        void* operator new (std::size_t size) throw (std::bad_alloc);
        cocos2d::Ref *_ref;
    public:
        DeferredRef(cocos2d::Ref *ref) {
            _ref = ref;
        }
        ~DeferredRef() {
            CC_SAFE_RELEASE_NULL(_ref);
        }
    };
}


#endif /* AIRef_h */
