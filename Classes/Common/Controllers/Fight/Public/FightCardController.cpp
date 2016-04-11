//
//  FightCardController.cpp
//  bvunity
//
//  Created by denis zaytcev on 4/5/16.
//
//

#include "FightCardController.hpp"

using namespace game;

FightCardContextTransitioning::FightCardContextTransitioning()
: _promise(nullptr)
{

}

FightCardContextTransitioning::~FightCardContextTransitioning() {
    CC_SAFE_RELEASE_NULL(_promise);
}

FightCardController* FightCardContextTransitioning::card() {
    return _card;
}

void FightCardContextTransitioning::setCard(FightCardController* card) {
    _card = card;
}

void FightCardContextTransitioning::setTransition(const Transition& transition) {
    _transition = transition;
}

FightCardContextTransitioning::Transition FightCardContextTransitioning::transition() {
    return _transition;
}

void FightCardContextTransitioning::completeTransition(bool didComplete) {
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (_completed == false) {
        auto result  = new Bolts::BFBool(didComplete);
        CC_SAFE_DEFRREDRELEASE(result);
        _promise->trySetResult(*result);
        _completed = true;
    }
}

Bolts::BFTask<Bolts::BFBool>* FightCardContextTransitioning::task() {
    return _promise->task();
}

void FightCardContextTransitioning::completeTransitionAsync(bool didComplete) {
    CC_SAFE_RETAIN(this);
    completeTransition(didComplete);
    
    std::thread([this](){
        CC_SAFE_RELEASE(this);
    }).detach();
}

bool FightCardContextTransitioning::isCompleted() {
    return _completed;
}

FightCardController::FightCardController()
: _assemblerCard(nullptr)
, delegate(nullptr)
{
}

FightCardController::~FightCardController() {}

bool FightCardController::init() {
    return true;
}

FightCardController* FightCardController::Create() {
    auto ref = new FightCardController();
    if (ref->init()) {
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return nullptr;
}

void FightCardController::viewDidLoad() {
    setCascadeOpacityEnabled(true);
    
    _assemblerCard = AssemblerCard::createWithSize(getContentSize());
    addChild(_assemblerCard);
}

FightCardController::Location FightCardController::location() {
    return Location::Undefined;
}

int FightCardController::x() {
}

int FightCardController::y() {
}

void FightCardController::commit(const internal::BVValueMap& map) {
    
    
    
}