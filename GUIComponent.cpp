//
// Created by Adam G.
//

#include "GUIComponent.h"

GUIComponent::GUIComponent() {

}

sf::Vector2f GUIComponent::getSize() {
    return size;
}

void GUIComponent::setSize(sf::Vector2f size) {
    this->size = size;
}

void GUIComponent::addEventHandler(sf::RenderWindow &window, sf::Event event) {

}
