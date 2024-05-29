//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_CURSORBLINK_H
#define CS008_SFML_TYPING_CURSORBLINK_H

#include <SFML/Graphics.hpp>
#include "GUIComponentAdapter.h"

class CursorBlink : public GUIComponentAdapter {
private:
    sf::RectangleShape line;
    sf::Clock blinkFrequency;
    int index = 0;
public:
    CursorBlink();

    int getIndex() const;
    void setIndex(int index);

    void setSize(sf::Vector2f size);

    virtual Snapshot getSnapshot();
    virtual void applySnapshot(const Snapshot& snapshot);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event) {};
    void update();
};


#endif //CS008_SFML_TYPING_CURSORBLINK_H
