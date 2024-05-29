//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_COLORSELECTOR_H
#define CS008_SFML_FINALPROJECT_COLORSELECTOR_H

#include <SFML/Graphics.hpp>
#include "GUIComponentAdapter.h"
#include "ColorBoxPicker.h"
#include "ColorHuePicker.h"

class ColorSelector : public GUIComponentAdapter {
private:
    sf::RectangleShape box;
    float boxSize = 32;

    MultiText label;

    ColorBoxPicker colorBoxPicker;
    ColorHuePicker colorHuePicker;
public:
    ColorSelector();

    void setLabel(const std::string& str);
    void setLabelSize(unsigned int s);

    std::function<void(const sf::Color&)> callBack;
    void setCallBack(std::function<void(const sf::Color&)> cb);

    virtual void setPosition(sf::Vector2f pos);

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_COLORSELECTOR_H
