//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_GUICOMPONENTADAPTER_H
#define CS008_SFML_TYPING_GUICOMPONENTADAPTER_H

#include "EventHandlerCallbacks.h"
#include "GUIComponent.h"
#include "History.h"

class GUIComponentAdapter : public GUIComponent, public EventHandlerCallbacks, public History {
public:
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_TYPING_GUICOMPONENTADAPTER_H
