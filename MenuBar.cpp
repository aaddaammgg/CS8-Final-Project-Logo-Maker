//
// Created by Adam G.
//

#include "MenuBar.h"

MenuBar::MenuBar() {

}

void MenuBar::addItem(MenuItem &menuItem) {
    if (!menuItemList.empty()) {
        sf::FloatRect backSize = menuItemList.back()->getLabelSize();
        sf::Vector2f backPos = menuItemList.back()->getPosition();

        menuItem.setPosition({backPos.x + backSize.width, backPos.y});
    }

    menuItemList.push_back(&menuItem);
}

void MenuBar::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (const auto &item: menuItemList) {
        window.draw(*item, states);
    }
}

void MenuBar::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
    for (auto &item: menuItemList) {
        item->addEventHandler(window, event);
    }
}

void MenuBar::update() {
    GUIComponentAdapter::update();

    for (auto &item: menuItemList) {
        item->update();
    }
}
