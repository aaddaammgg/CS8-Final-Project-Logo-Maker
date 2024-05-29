//
// Created by Adam G.
//

#include "ItemList.h"

#include <utility>

ItemList::ItemList() {

}

void ItemList::addItem(Item *item) {
    if (!isEmpty()) {
        sf::Vector2f backSize = itemList.back()->getSize();
        sf::Vector2f backPos = itemList.back()->getPosition();

        item->setPosition({backPos.x, backPos.y + backSize.y});
    }

    itemList.push_back(item);
}

void ItemList::addItem(Item &item, std::function<void(std::string)> cb) {
    addItem(&item);
    itemList.back()->setCallBack(std::move(cb));
}

std::vector<Item*> &ItemList::getItemList() {
    return itemList;
}

bool ItemList::isEmpty() {
    return itemList.empty();
}

void ItemList::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (!isEnabled(HIDDEN)) {
        states.transform *= getTransform();

        for (const auto &item: itemList) {
            window.draw(*item, states);
        }
    }
}

void ItemList::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void ItemList::update() {
    if (!isEnabled(HIDDEN)) {
        GUIComponentAdapter::update();

        for (auto &item: itemList) {
            item->update();
        }
    }
}
