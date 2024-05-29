//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_ITEM_H
#define CS008_SFML_FINALPROJECT_ITEM_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIComponentAdapter.h"
#include "MultiText.h"

class Item : public GUIComponentAdapter {
private:
    sf::RectangleShape box;
    MultiText mt;
public:
    Item();

    MultiText& getMultiText();
    sf::RectangleShape& getBox();

    virtual void setSize(sf::Vector2f size);

    std::function<void(std::string)> callBack;
    void setCallBack(std::function<void(std::string)> cb);

    std::string getString();

    void setString(const std::string& str);
    void setString(const MultiText& multiText);
    void setString(const Letter& ltr);

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_ITEM_H
