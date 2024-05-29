//
// Created by Adam G.
//

#include "DisplayLogo.h"

DisplayLogo::DisplayLogo() {
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);
    box.setPosition({3,3});

    shadow.setScale({1, -1});
    shadow.setOpacity(0);
}

sf::RectangleShape &DisplayLogo::getBox() {
    return box;
}

MultiText &DisplayLogo::getLogo() {
    return logo;
}

MultiText &DisplayLogo::getShadow() {
    return shadow;
}

void DisplayLogo::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);

    size.x -= 6;
    size.y -= 6;
    box.setSize(size);
}

void DisplayLogo::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();

    window.draw(box, states);
    window.draw(logo, states);
    window.draw(shadow, states);
}

void DisplayLogo::update() {
    logo.update();
    shadow.update();
}
