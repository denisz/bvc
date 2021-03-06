//
//  IReactionController.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/10/16.
//
//

#include "IReactionController.hpp"

using namespace game;
using namespace common;

IReactionController::IReactionController()
: _reaction(nullptr)
, _autoSubscribeReaction(true) {

}

IReactionController::~IReactionController() {
    CC_SAFE_RELEASE_NULL(_reaction);
}

bool IReactionController::init() {
    auto reaction = Reaction::create();
    CC_SAFE_DEFRREDRELEASE(reaction);
    return initWithReaction(reaction);
}

bool IReactionController::initWithReaction(Reaction* reaction) {
    _reaction = reaction;
    _reaction->delegate = this;
    CC_SAFE_RETAIN(_reaction);
    
    if (_autoSubscribeReaction) {
        subscribe();
    }
    
    return true;
}

void IReactionController::reactionMainThread() {
    if (_reaction != nullptr)
        _reaction->setMode(false);
}

void IReactionController::reactionMultiThread() {
    if (_reaction != nullptr)
        _reaction->setMode(true);
}

void IReactionController::processMessage(internal::network::Response& res) {
}

void IReactionController::processError(internal::network::Response& res) {
}

void IReactionController::processClose() {
}

void IReactionController::processOpen() {
}

void IReactionController::didSubscribe() {
}

void IReactionController::didUnsubscribe() {
}

void IReactionController::subscribe() {
    if (_reaction != nullptr)
        _reaction->subscribe();
}
void IReactionController::unsubscribe() {
    if (_reaction != nullptr)
        _reaction->unsubscribe();
}


