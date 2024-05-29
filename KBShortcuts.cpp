//
// Created by Adam G.
//

#include "KBShortcuts.h"

bool KBShortcuts::isControl() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}

bool KBShortcuts::isUndo() {
    return isControl() && sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
}

bool KBShortcuts::isRedo() {
    return isControl() && sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
}
