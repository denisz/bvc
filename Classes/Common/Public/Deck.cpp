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

Deck* Deck::create() {
    auto ref = new Deck();
    if (ref->init("deck")) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

Deck* Deck::createWithCards(BVValueMap &cards) {
    auto ref = new Deck();
    
    if (ref->init("deck")) {
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

void Deck::setOwner() {}

void Deck::getCards() {}

bool Deck::containCard(const std::string& card) {
    return true;
}

bool isOwnerCurrentUser() {
    return true;
}