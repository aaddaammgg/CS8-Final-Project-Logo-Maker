//
// Created by Adam G.
//

#include "DropdownMenu.h"

#include <utility>

DropdownMenu::DropdownMenu() {
    itemList.enableState(HIDDEN);
    disableState(OPEN);
}

DropdownMenu::~DropdownMenu() {
    for (auto& item : itemList.getItemList()) {
        delete item;
    }
}

Snapshot DropdownMenu::getSnapshot() {
    Snapshot s;
    s.setData(inputBox.getMultiText());
    
    return s;
}

void DropdownMenu::applySnapshot(const Snapshot &snapshot) {
    inputBox.getMultiText() = snapshot.getData();
}

void DropdownMenu::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
    inputBox.setSize(size);

    for (auto& item : itemList.getItemList()) {
        item->setSize(size);
    }
    
    itemList.setPosition(0, size.y + 1);
}

void DropdownMenu::addItem(const std::string& str) {
    Item* item = new Item();
    item->setString(str);
    item->setSize(getSize());

    if (itemList.isEmpty()) {
        inputBox.setSelectedItem(*item);
    }

    itemList.addItem(item);
}

std::string DropdownMenu::getString(int i) {
    return itemList.getItemList()[i]->getString();
}

std::string DropdownMenu::getSelected() {
    return inputBox.getSelectedItem().getString();
}

int DropdownMenu::getIndex() const {
    return index;
}

void DropdownMenu::setIndex(int i) {
    if (i < 0) {
        i = 0;
    } else if (i > itemList.getItemList().size()) {
        i = (int)itemList.getItemList().size();
    }

    index = i;

    inputBox.setSelectedItem(*itemList.getItemList()[index]);
    if (callBack != nullptr) {
        callBack(i);
    }
}

void DropdownMenu::setCallBack(std::function<void(const int&)> cb) {
    callBack = std::move(cb);
}

void DropdownMenu::onKeyPressed(const sf::Event::KeyEvent &key) {
    if (!isEnabled(SELECTED)) return;

    if (KBShortcuts::isUndo()) {
        std::cout << "Control + Z" << std::endl;

        if (getUndoSize() == 0 || inputBox.getMultiText().getCharCount() == 0) {
            return;
        }

        if (getUndoTop().snapshot.getData().getString() == inputBox.getMultiText().getString()) {
            undoPop();
        }

        if (getUndoSize() != 0) {
            applySnapshot(getUndoTop().snapshot);
            undoPop();
        }
    }

    if (KBShortcuts::isRedo()) {
        std::cout << "Control + Y" << std::endl;

        if (getRedoSize() == 0) {
            return;
        }

        if (getRedoTop().snapshot.getData().getString() == inputBox.getMultiText().getString()) {
            redoPop();
        }

        if (getRedoSize() != 0) {
            applySnapshot(getRedoTop().snapshot);
            redoPop();
        }
    }
}

void DropdownMenu::onMouseMoved(sf::Vector2f pos) {
    for (auto& item : itemList.getItemList()) {
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

void DropdownMenu::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
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
            int i = 0;
            for (auto& item : itemList.getItemList()) {
                sf::FloatRect itemBounds = item->getBox().getGlobalBounds();
                sf::Vector2f itemPos = item->getPosition();

                itemBounds.top += itemPos.y;
                itemBounds.top += item->getSize().y;

                sf::FloatRect itemPosTransform = getTransform().transformRect(itemBounds);

                if (itemPosTransform.contains(pos)) {
                    if (!getInit()) {
                        HistoryNode hn;
                        hn.snapshot = getSnapshot();
                        hn.component = this;
                        undoPush(hn);
                        setInit(true);
                    }

                    inputBox.setSelectedItem(*item);
                    index = i;

                    HistoryNode hn;
                    hn.snapshot = getSnapshot();
                    hn.component = this;
                    undoPush(hn);

                    enableState(SELECTED);

                    if (callBack != nullptr) {
                        callBack(i);
                    }
                }

                i++;
            }
        }
        disableState(OPEN);
        itemList.enableState(HIDDEN);
    }
}

void DropdownMenu::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(itemList, states);
    window.draw(inputBox, states);
}

void DropdownMenu::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void DropdownMenu::update() {
    GUIComponentAdapter::update();
    itemList.update();
    inputBox.update();
}
