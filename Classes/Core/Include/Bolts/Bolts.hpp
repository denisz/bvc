//
//  Bolts.hpp
//  Bolts
//
//  Created by denis zaytcev on 2/10/16.
//  Copyright © 2016 denis zaytcev. All rights reserved.
//

#ifndef Bolts_hpp
#define Bolts_hpp

#include "BFCancellationToken.hpp"
#include "BFTask.hpp"
#include "BFTaskCompletionSource.hpp"
#include "BFTaskCompletionAfter.hpp"
#include <string>

namespace Bolts {
    class Bolts {
    public:
        const std::string version() {
            return "0.0.1";
        }
    };

}

#endif /* Bolts_hpp */
