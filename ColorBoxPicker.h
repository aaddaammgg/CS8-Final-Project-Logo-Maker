//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_COLORBOXPICKER_H
#define CS008_SFML_FINALPROJECT_COLORBOXPICKER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIComponentAdapter.h"

class ColorBoxPicker : public GUIComponentAdapter {
public:
    typedef enum {
        RED,
        GREEN,
        BLUE,
        CYAN,
        YELLOW,
        ORANGE,
        MAGENTA,
        PINK,

        LAST_COLORS
    } COLOR;
private:
    sf::RectangleShape colors[LAST_COLORS];

    COLOR selected = RED;
    float boxSize = 32;
    static sf::Color getColor(COLOR c);
    void updateSize();
public:
    ColorBoxPicker();

    sf::Color getColor();

    std::function<void(const sf::Color&)> callBack;
    void setCallBack(std::function<void(const sf::Color&)> cb);

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f pos);
    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);

    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event) override;
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_COLORBOXPICKER_H
