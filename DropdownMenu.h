//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_DROPDOWNMENU_H
#define CS008_SFML_FINALPROJECT_DROPDOWNMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "GUIComponentAdapter.h"
#include "ItemList.h"
#include "InputBox.h"

class DropdownMenu : public GUIComponentAdapter {
private:
    ItemList itemList;
    InputBox inputBox;
    int index = 0;
public:
    DropdownMenu();
    ~DropdownMenu();

    virtual Snapshot getSnapshot();
    virtual void applySnapshot(const Snapshot& snapshot);

    virtual void setSize(sf::Vector2f size);

    void addItem(const std::string& str);

    std::string getString(int i);
    std::string getSelected();

    int getIndex() const;
    void setIndex(int i);

    std::function<void(const int&)> callBack;
    void setCallBack(std::function<void(const int&)> cb);

    virtual void onKeyPressed(const sf::Event::KeyEvent& key);
    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onMouseMoved(sf::Vector2f pos);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_DROPDOWNMENU_H
