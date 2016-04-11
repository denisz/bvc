//
//  DeckController.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/16/16.
//
//

#ifndef DeckController_hpp
#define DeckController_hpp

#include "stdafx.h"
#include "ICommandController.hpp"

using namespace common;

namespace game {
    class DeckController: public internal::AIRef, public ICommandController {
    public:
        
        CommandRunner::Handler* list();
        CommandRunner::Handler* remove(const std::string& deckId);
        CommandRunner::Handler* copy(const internal::BVValueMap& data);
        CommandRunner::Handler* save(const internal::BVValueMap& data);
        CommandRunner::Handler* create(const internal::BVValueMap& data);

        CommandRunner::Handler* addBookmark(const std::string& deckId);
        CommandRunner::Handler* removeBookmark(const std::string& deckId);

        CommandRunner::Handler* rename(const std::string& deckId, const std::string& names);
        CommandRunner::Handler* changeCover(const std::string& deckId, const std::string& cover);
        
        virtual bool init();
        BV_CREATE_FUNC(DeckController);
    };
}

#endif /* DeckController_hpp */
