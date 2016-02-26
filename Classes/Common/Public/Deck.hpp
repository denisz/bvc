//
//  Deck.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#ifndef Deck_hpp
#define Deck_hpp

#include "stdafx.h"
#include "Object.hpp"

//реализовать список колод пользователя
namespace game {
    class Deck: public game::Object {
        void setCards(BVValueMap& cards);
        void setOwner();
        void getCards();
        bool containCard(const std::string& card);
        bool isOwnerCurrentUser();
        void setName();
        
        CommandRunner::Handler* saveInBackground();
        void saveEventually();
        
        CommandRunner::Handler* deleteInBackground();
        void deleteEventually();
        
    public:
        static Deck* create();
        static Deck* createWithCards(BVValueMap& cards);
    };
}

#endif /* Deck_hpp */
