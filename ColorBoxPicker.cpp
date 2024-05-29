//
// Created by Adam G.
//

#include "ColorBoxPicker.h"

ColorBoxPicker::ColorBoxPicker() {
    int i = 0;
    for (auto & box : colors) {
        box.setSize({boxSize, boxSize});
        box.setPosition({static_cast<float>(i * boxSize), 0});
        box.setFillColor(getColor(static_cast<COLOR>(i)));
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color::White);
        i++;
    }

    enableState(HIDDEN);
    disableState(DISABLED);
    disableState(SELECTED);
    disableState(CLICKED);
}

sf::Color ColorBoxPicker::getColor(ColorBoxPicker::COLOR c) {
    switch (c) {
        case RED:
            return sf::Color::Red;
        case GREEN:
            return sf::Color::Green;
        case BLUE:
            return sf::Color::Blue;
        case CYAN:
            return sf::Color::Cyan;
        case YELLOW:
            return sf::Color::Yellow;
        case ORANGE:
            return {255, 165, 0};
        case MAGENTA:
            return sf::Color::Magenta;
        case PINK:
            return {255,105,180};
        default:
            return {0, 0, 0};
    }
}

sf::Color ColorBoxPicker::getColor() {
    return getColor(selected);
}

void ColorBoxPicker::setCallBack(std::function<void(const sf::Color &)> cb) {
    callBack = std::move(cb);
}

void ColorBoxPicker::updateSize() {
    float width = colors[LAST_COLORS - 1].getPosition().x + colors[LAST_COLORS - 1].getSize().x;
    setSize({width, boxSize});
}

void ColorBoxPicker::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
}

void ColorBoxPicker::setPosition(sf::Vector2f pos) {
    GUIComponent::setPosition(pos);

    int i = 0;
    for (auto & box : colors) {
        box.setPosition({static_cast<float>(i * boxSize), 0});
        i++;
    }

    updateSize();
}

void ColorBoxPicker::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    if (button != sf::Mouse::Left) return;

    int i = 0;
    for (auto & box : colors) {
        sf::FloatRect boxBounds = box.getGlobalBounds();
        sf::FloatRect boxPosTransform = getTransform().transformRect(boxBounds);

        if (boxPosTransform.contains(pos)) {
            selected = static_cast<COLOR>(i);
            if (callBack != nullptr) {
                callBack(getColor(selected));
            }
        }

        i++;
    }
}

void ColorBoxPicker::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    if (isEnabled(HIDDEN) || isEnabled(DISABLED)) {
        return;
    }

    GUIComponentAdapter::addEventHandler(window, event);
}

void ColorBoxPicker::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (isEnabled(HIDDEN)) {
        return;
    }

    states.transform *= getTransform();
//    window.draw(label, states);
    for (auto & box : colors) {
        window.draw(box, states);
    }
}

void ColorBoxPicker::update() {
    GUIComponentAdapter::update();
}
