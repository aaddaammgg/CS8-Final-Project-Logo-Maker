//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_GUICOMPONENT_H
#define CS008_SFML_TYPING_GUICOMPONENT_H

#include <SFML/Graphics.hpp>
#include "States.h"
#include "KBShortcuts.h"
#include "SnapshotInterface.h"

class GUIComponent : public sf::Drawable, public sf::Transformable, public States, public SnapshotInterface {
private:
    sf::Vector2f size = {10, 10};
public:
    GUIComponent();

    sf::Vector2f getSize();
    virtual void setSize(sf::Vector2f size);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void update() = 0;
};


#endif //CS008_SFML_TYPING_GUICOMPONENT_H
