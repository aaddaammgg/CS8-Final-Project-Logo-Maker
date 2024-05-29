//
// Created by Adam G.
//

#include "GUIComponentAdapter.h"

void GUIComponentAdapter::draw(sf::RenderTarget &window, sf::RenderStates states) const {

}

void GUIComponentAdapter::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    EventHandlerCallbacks::addEventHandler(window, event);
}

void GUIComponentAdapter::update() {

}
