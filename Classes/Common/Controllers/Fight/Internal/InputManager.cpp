//
//  InputManager.cpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#include "InputManager.hpp"

using namespace game;

InputManager::InputManager() {
    _delegates = std::forward_list<InputManager::Delegate*>();
}

InputManager::~InputManager() {
    _delegates.clear();
}

bool InputManager::init() {
    return true;
}

void InputManager::addDelegate(Delegate *delegate) {
    _delegates.push_front(delegate);
}

void InputManager::removeDelegate(Delegate *delegate) {
    _delegates.remove(delegate);
}

void InputManager::setEnabled(bool enabled) {
    _enabled = enabled;
}

void InputManager::didTapCard(int card) {
    auto cancel = CancellationToken();
    for (auto &item: _delegates) {
        if (!cancel.isCancel()) {
            item->didTapCard(card, cancel);
        }
    }
}

void InputManager::didTapCell(int x, int y) {
    auto cancel = CancellationToken();
    for (auto &item: _delegates) {
        if (!cancel.isCancel()) {
            item->didTapCell(x, y, cancel);
        }
    }
}

void InputManager::didTapPass() {
    auto cancel = CancellationToken();
    for (auto &item: _delegates) {
        if (!cancel.isCancel()) {
            item->didTapPass(cancel);
        }
    }
}

void InputManager::didTapComplete() {
    auto cancel = CancellationToken();
    for (auto &item: _delegates) {
        if (!cancel.isCancel()) {
            item->didTapComplete(cancel);
        }
    }
}
