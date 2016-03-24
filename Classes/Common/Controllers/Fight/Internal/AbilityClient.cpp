//
//  AbilityClient.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#include "AbilityClient.hpp"

using namespace game;


AbilityClient::AbilityClient() {
}

AbilityClient::~AbilityClient() {
}

bool AbilityClient::init() {
    return true;
}

void AbilityClient::addAbility(Ability ability, bool clear) {
    
}

void AbilityClient::clearSession() {
    
}

bool AbilityClient::card(int cardid) {
    return true;
}

bool AbilityClient::cell(int x, int y) {
    return true;
}

bool AbilityClient::complete() {
    return true;
}

bool AbilityClient::pass() {
    return true;
}

void AbilityClient::didTapCard(int cardid, InputManager::CancellationToken& cancel) {
    if (card(cardid)) {
        cancel.cancel();
    }
}

void AbilityClient::didTapCell(int x, int y, InputManager::CancellationToken& cancel) {
    if (cell(x, y)) {
        cancel.cancel();
    }
}

void AbilityClient::didTapPass(InputManager::CancellationToken& cancel) {
    if (pass()) {
        cancel.cancel();
    }
}

void AbilityClient::didTapComplete(InputManager::CancellationToken& cancel) {
    if (complete()) {
        cancel.cancel();
    }
}

AbilityClient::Ability AbilityClient::createAbility(const internal::BVValue &data) {
    if (data.getType() == internal::BVValue::Type::MAP) {
        return createAbility(data.asValueMap());
    }
    return createAbility(internal::BVValueMap());
}

AbilityClient::Trend AbilityClient::createTrend(const internal::BVValue &data) {
    if (data.getType() == internal::BVValue::Type::MAP) {
        return createTrend(data.asValueMap());
    }
    return createTrend(internal::BVValueMap());
}

AbilityClient::Trend AbilityClient::createTrend(const internal::BVValueMap &data) {
    Trend trend = Trend();
    trend.type = Trend::Type::NONE;
    
    auto end    = data.end();
    auto x      = data.find("x");
    auto y      = data.find("y");
    auto c      = data.find("c");
    
    if (x != end) {
        trend.type = Trend::Type::CELL;
        trend.x = x->second.asInt();
    }
    
    if (y != end) {
        trend.type = Trend::Type::CELL;
        trend.y = y->second.asInt();
    }
    
    if (c != end) {
        trend.type = Trend::Type::CARD;
        trend.c = c->second.asInt();
    }
    
    return trend;
}

AbilityClient::Ability AbilityClient::createAbility(const internal::BVValueMap &data) {
    Ability abl = Ability();
    
    abl.type            = Ability::Type::ABILITY;
    abl.targets         = std::vector<Trend>();
    abl.selectedTargets = std::vector<Trend>();
    abl.maxTargets      = 1;
    abl.minTargets      = 1;
    abl.canPass         = true;
    abl.canEarlyComplete= true;
    
    auto targets = data.find("targets");
    if (targets != data.end()) {
        auto targetsVector = targets->second.asValueVector();
        for (auto &item: targetsVector) {
            auto trend = createTrend(item);
            abl.targets.push_back(trend);
        }
    }
    
    auto abilityId = data.find("id");
    if (abilityId != data.end()) {
        abl.abilityId = abilityId->second.asInt();
    }
    
    return abl;
}

AbilityClient::Ability AbilityClient::createAbilityFromDialog(const internal::BVValue &dialog) {
    Ability abl;
    
    abl.type            = Ability::Type::DIALOG;
    abl.targets         = std::vector<Trend>();
    abl.selectedTargets = std::vector<Trend>();
    abl.maxTargets      = 1;
    abl.minTargets      = 1;
    abl.canPass         = true;
    abl.canEarlyComplete= true;
    
    
    return abl;
}