//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_MENUBAR_H
#define CS008_SFML_FINALPROJECT_MENUBAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "GUIComponentAdapter.h"
#include "MenuItem.h"

class MenuBar : public GUIComponentAdapter {
private:
    std::vector<MenuItem*> menuItemList;
public:
    MenuBar();

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void setSize(sf::Vector2f size) {};

    void addItem(MenuItem& menuItem);

//    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);
//    virtual void onMouseMoved(sf::Vector2f pos);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_MENUBAR_H
