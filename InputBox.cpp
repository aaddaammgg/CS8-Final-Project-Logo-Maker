//
// Created by Adam G.
//

#include "InputBox.h"

InputBox::InputBox() {

}

Item &InputBox::getSelectedItem() {
    return selectedItem;
}

void InputBox::setSelectedItem(Item &item) {
    selectedItem.setSize(item.getSize());
    selectedItem.getMultiText() = item.getMultiText();
}

MultiText &InputBox::getMultiText() {
    return selectedItem.getMultiText();
}

sf::FloatRect InputBox::getGlobalBounds() {
    return selectedItem.getBox().getGlobalBounds();
}

void InputBox::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(selectedItem, states);
}

void InputBox::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void InputBox::update() {
    GUIComponentAdapter::update();
    selectedItem.update();
}
