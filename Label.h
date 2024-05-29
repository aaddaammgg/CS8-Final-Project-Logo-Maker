//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_LABEL_H
#define CS008_SFML_TYPING_LABEL_H

#include <SFML/Graphics.hpp>
#include "GUIComponentAdapter.h"

class Label : public GUIComponentAdapter {
private:
    sf::Text label;
public:
    Label();

    std::string getLabelString();
    int getLabelSize();

    void setLabel(const std::string& str);
    void setLabelSize(const int& size);
    void setLabelColor(const sf::Color& color);

    sf::FloatRect getGlobalBounds();

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event) {};
    void update() {};
};


#endif //CS008_SFML_TYPING_LABEL_H
