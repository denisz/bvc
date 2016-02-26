//
//  DataSourceController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/24/16.
//
//

#ifndef DataSourceController_hpp
#define DataSourceController_hpp

#include "stdafx.h"
#include "GameController.hpp"
namespace game {
    class DataSourceController: public GameController {
    public:
        typedef internal::BVValueMap Context;
        
    public:
        Context* _context;
        enum class Options {CREATE, REPLACE, UPDATE, DELETE};
        class Delegate {
        public:
            virtual void didChange(Options options, internal::BVValue &value, Context& context) {};
            virtual void willChange(Options options, internal::BVValue &value, Context& context) {};
        };
    protected:
        virtual bool init();
    public:
        DataSourceController();
        Delegate* dataSourceDelegate;
    };
}

#endif /* DataSourceController_hpp */
