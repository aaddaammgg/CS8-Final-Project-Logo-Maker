//
// Created by Adam G.
//

#include "Label.h"

Label::Label() {
    label.setFont(ResourceHolder::getFont("Roboto-Regular.ttf"));
    label.setFillColor(sf::Color::Black);
    label.setCharacterSize(12);
}

std::string Label::getLabelString() {
    return label.getString();
}

int Label::getLabelSize() {
    return label.getCharacterSize();
}

void Label::setLabel(const std::string& str) {
    label.setString(str);
}

void Label::setLabelSize(const int &size) {
    label.setCharacterSize(size);
}

void Label::setLabelColor(const sf::Color &color) {
    label.setFillColor(color);
}

sf::FloatRect Label::getGlobalBounds() {
    return label.getGlobalBounds();
}

void Label::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(label, states);
}
