//
//  Deck.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/20/16.
//
//

#include "Deck.hpp"

using namespace internal;
using namespace game;

const std::string kKeyDeckClassName = "user";

Deck* Deck::create() {
    auto ref = new Deck();
    if (ref->init(kKeyDeckClassName)) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

Deck* Deck::createWithCards(BVValueMap &cards) {
    auto ref = new Deck();
    
    if (ref->init(kKeyDeckClassName)) {
        ref->setCards(cards);
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

CommandRunner::Handler* Deck::saveInBackground() {
    auto data = this->data();
    return Plugins::deckController()->save(*data);
}

void Deck::saveEventually() {
    auto data = this->data();
    Plugins::deckController()->save(*data)->continueWithBlock([](CommandRunner::Handler *task)->CommandRunner::Handler* {
        
        if (task->hasError()) {
//        ServiceLocator::eventually()->deferredRequest(internal::network::Request &req)
        }

        return nullptr;
    });
}

CommandRunner::Handler* Deck::deleteInBackground() {
    return Plugins::deckController()->remove(objectId());
}

void Deck::deleteEventually() {
    Plugins::deckController()->remove(objectId())->continueWithBlock([](CommandRunner::Handler *task)->CommandRunner::Handler* {
        
        if (task->hasError()) {
//        ServiceLocator::eventually()->deferredRequest(internal::network::Request &req)
        }
        
        return nullptr;
    });
}

void Deck::setCards(BVValueMap& cards) {
    setObject(cards, "cards");
}

void Deck::setOwner() {
}

void Deck::getCards() {
//    auto cards = std::map<std::string, int>();
//    
//    return cards;
}

std::string Deck::localizedName() {
    return "";
}

bool Deck::containCard(const std::string& card) {
    return true;
}

bool isOwnerCurrentUser() {
    return true;
}