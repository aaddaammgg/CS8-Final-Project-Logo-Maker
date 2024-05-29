//
// Created by Adam G.
//

#include "MenuItem.h"

#include <utility>

MenuItem::MenuItem() : MenuItem("Menu") {

}

MenuItem::MenuItem(const std::string& str) {
    itemList.enableState(HIDDEN);
    disableState(OPEN);

    Item item;
    item.setString(str);

    sf::Vector2f size = {item.getMultiText().getSize().width + 50,40};

    item.setSize(size);
    inputBox.setSelectedItem(item);
    itemList.setPosition(0, size.y + 2);
}

sf::FloatRect MenuItem::getLabelSize() {
    return inputBox.getGlobalBounds();
}

void MenuItem::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
//    inputBox.setSize(boxSize);

    for (auto& item : itemList.getItemList()) {
        item->setSize(size);
    }

//    itemList.setPosition(0, boxSize.y + 1);
}

void MenuItem::addItem(const std::string& str) {
    addItem(str, nullptr);
}

void MenuItem::addItem(const std::string &str, std::function<void(std::string)> cb) {
    Item *item = new Item();
    item->setString(str);
    item->setSize(getSize());
    item->setCallBack(std::move(cb));

    itemList.addItem(item);
}

void MenuItem::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    if (button != sf::Mouse::Left) return;

    sf::FloatRect boxPos = getTransform().transformRect(inputBox.getGlobalBounds());

    if (boxPos.contains(pos)) {
        enableState(SELECTED);
        if (isEnabled(OPEN)) {
            disableState(OPEN);
            itemList.enableState(HIDDEN);
        } else {
            enableState(OPEN);
            itemList.disableState(HIDDEN);
        }
    } else {
        disableState(SELECTED);
        if (isEnabled(OPEN)) {
            for (auto& item : itemList.getItemList()) {
                sf::FloatRect itemBounds = item->getBox().getGlobalBounds();
                sf::Vector2f itemPos = item->getPosition();

                itemBounds.top += itemPos.y;
                itemBounds.top += item->getSize().y;

                sf::FloatRect itemPosTransform = getTransform().transformRect(itemBounds);

                if (itemPosTransform.contains(pos)) {
//                    inputBox.setSelectedItem(item);
                    enableState(SELECTED);

                    if (item->callBack != nullptr) {
                        item->callBack(item->getString());
                    }
                }
            }
        }
        disableState(OPEN);
        itemList.enableState(HIDDEN);
    }
}

void MenuItem::onMouseMoved(sf::Vector2f pos) {
    for (auto &item : itemList.getItemList()) {
        sf::FloatRect itemBounds = item->getBox().getGlobalBounds();
        sf::Vector2f itemPos = item->getPosition();

        itemBounds.top = itemPos.y;
        itemBounds.top += item->getSize().y;

        itemBounds.height -= (item->getBox().getOutlineThickness() * 2);

        sf::FloatRect itemPosTransform = getTransform().transformRect(itemBounds);

        if (itemPosTransform.contains(pos)) {
            item->getBox().setFillColor(sf::Color::Red);
        } else {
            item->getBox().setFillColor(sf::Color::Black);
        }
    }
}

void MenuItem::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(itemList, states);
    window.draw(inputBox, states);
}

void MenuItem::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void MenuItem::update() {
    GUIComponentAdapter::update();
    itemList.update();
    inputBox.update();
}
