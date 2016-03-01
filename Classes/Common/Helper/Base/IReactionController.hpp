//
//  IReactionController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#ifndef IReactionController_hpp
#define IReactionController_hpp

#include "stdafx.h"
#include "Reaction.hpp"

namespace game {
    class IReactionController: public common::Reaction::Delegate {
    protected:
        virtual void processMessage(internal::network::Response& res);
        virtual void processError(internal::network::Response& res);
        virtual void processClose();
        virtual void processOpen();
        virtual void didSubscribe();
        virtual void didUnsubscribe();
        
        bool _autoSubscribeReaction;
    private:
        common::Reaction* _reaction;
    public:
        IReactionController();
        ~IReactionController();
        virtual bool init();
        virtual bool initWithReaction(common::Reaction* reaction);
        
        virtual void subscribe();
        virtual void unsubscribe();
    };
}

#endif /* IReactionController_hpp */
