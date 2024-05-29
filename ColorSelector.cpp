//
// Created by Adam G.
//

#include "ColorSelector.h"

ColorSelector::ColorSelector() {
    box.setSize({boxSize, boxSize});
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(1);

    colorBoxPicker.setCallBack([&](const sf::Color& color) {
        box.setFillColor(color);
        colorHuePicker.setHUE(color);

        if (callBack != nullptr) {
            callBack(color);
        }
    });

    colorHuePicker.setCallBack([&](const sf::Color& color) {
        box.setFillColor(color);

        if (callBack != nullptr) {
            callBack(color);
        }
    });
}

void ColorSelector::setLabel(const std::string &str) {
    label = str;
    setPosition(getPosition());
}

void ColorSelector::setLabelSize(unsigned int s) {
    label.setCharacterSize(s);
    setPosition(getPosition());
}

void ColorSelector::setCallBack(std::function<void(const sf::Color &)> cb) {
    callBack = std::move(cb);
}

void ColorSelector::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    if (button != sf::Mouse::Left) return;
    sf::FloatRect boxPos = getTransform().transformRect(box.getGlobalBounds());

    if (boxPos.contains(pos)) {
        enableState(SELECTED);
        if (isEnabled(OPEN)) {
            disableState(OPEN);
            colorBoxPicker.enableState(HIDDEN);
            colorHuePicker.enableState(HIDDEN);
        } else {
            enableState(OPEN);
            colorBoxPicker.disableState(HIDDEN);
            colorHuePicker.disableState(HIDDEN);
        }
    }
}

void ColorSelector::setPosition(sf::Vector2f pos) {
    GUIComponentAdapter::setPosition(pos);
    float labelWidth = label.getSize().width;
    auto labelHeight = (float)label.getCharacterSize() + 20;
    box.setPosition(labelWidth + 10, 5);
    colorBoxPicker.setPosition({pos.x, pos.y + labelHeight});
    colorHuePicker.setPosition({pos.x, pos.y + labelHeight + colorBoxPicker.getSize().y + 10});
}

void ColorSelector::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(label, states);
    window.draw(box, states);
    window.draw(colorBoxPicker);
    window.draw(colorHuePicker);
}

void ColorSelector::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
    colorBoxPicker.addEventHandler(window, event);
    colorHuePicker.addEventHandler(window, event);
}

void ColorSelector::update() {
    GUIComponentAdapter::update();
}
