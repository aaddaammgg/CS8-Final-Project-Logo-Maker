//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_INPUTBOX_H
#define CS008_SFML_FINALPROJECT_INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GUIComponentAdapter.h"
#include "Item.h"

class InputBox : public GUIComponentAdapter {
private:
    Item selectedItem;
public:
    InputBox();

    Item& getSelectedItem();
    void setSelectedItem(Item& item);

    MultiText& getMultiText();

    sf::FloatRect getGlobalBounds();

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_INPUTBOX_H
