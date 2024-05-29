//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_MENUITEM_H
#define CS008_SFML_FINALPROJECT_MENUITEM_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIComponentAdapter.h"
#include "ItemList.h"
#include "InputBox.h"

class MenuItem : public GUIComponentAdapter {
private:
    ItemList itemList;
    InputBox inputBox;
public:
    MenuItem();
    MenuItem(const std::string& str);

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    sf::FloatRect getLabelSize();

    virtual void setSize(sf::Vector2f size);

    void addItem(const std::string& str);
    void addItem(const std::string& str, std::function<void(std::string)> cb);

    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onMouseMoved(sf::Vector2f pos);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();

};


#endif //CS008_SFML_FINALPROJECT_MENUITEM_H
