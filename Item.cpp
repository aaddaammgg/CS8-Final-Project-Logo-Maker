//
// Created by Adam G.
//

#include "Item.h"

Item::Item() {
//    enableState(HIDDEN);
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    mt.setAlignment(MultiText::ALIGN::CENTER);
}

MultiText &Item::getMultiText() {
    return mt;
}

sf::RectangleShape &Item::getBox() {
    return box;
}

void Item::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
    box.setSize(size);
    mt.setPosition(size.x / 2,0);
}

void Item::setCallBack(std::function<void(std::string)> cb) {
    callBack = std::move(cb);
}

std::string Item::getString() {
    return mt.getString();
}

void Item::setString(const std::string& str) {
    for (auto& i : str) {
        mt.addChar(i);
    }
}

void Item::setString(const MultiText& multiText) {
    mt = multiText;
}

void Item::setString(const Letter& ltr) {
    mt.addChar(ltr);
}

void Item::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (!isEnabled(HIDDEN)) {
        states.transform *= getTransform();
        window.draw(box, states);
        window.draw(mt, states);
    }

}

void Item::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void Item::update() {
    GUIComponentAdapter::update();
    if (!isEnabled(HIDDEN)) {
        mt.update();
    }
}
