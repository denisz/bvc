//
//  TransitionManager.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/25/16.
//
//

#include "TransitionManager.hpp"

using namespace game;

TransitionManager::TransitionManager() {
    
}

bool TransitionManager::init() {
    return true;
}

void TransitionManager::animateTransition(UIViewControllerContextTransitioning* transitionContext) {
    transitionContext->completeTransition();
    
}

time_t TransitionManager::transitionDuration(UIViewControllerContextTransitioning* transitionContext) {
    return 0.0;
}
