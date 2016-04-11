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
    public:
        void setName();
        void setOwner();
        void getCards();
        bool isOwnerCurrentUser();
        std::string localizedName();
        void setCards(BVValueMap& cards);
        bool containCard(const std::string& card);
        
        void saveEventually();
        void deleteEventually();
        
        CommandRunner::Handler* saveInBackground();
        CommandRunner::Handler* deleteInBackground();
        
        
    public:
        static Deck* create();
        static Deck* createWithCards(BVValueMap& cards);
    };
}

#endif /* Deck_hpp */
