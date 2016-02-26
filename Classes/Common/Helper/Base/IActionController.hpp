//
//  IActionController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/22/16.
//
//

#ifndef IActionController_hpp
#define IActionController_hpp

#include "stdafx.h"

namespace game {
    class IActionController {
        virtual void subscribe();
        virtual void unsubscribe();
    };
}

#endif /* IActionController_hpp */
