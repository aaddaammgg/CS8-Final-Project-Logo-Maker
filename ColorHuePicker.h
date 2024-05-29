//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_COLORHUEPICKER_H
#define CS008_SFML_FINALPROJECT_COLORHUEPICKER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIComponentAdapter.h"

class ColorHuePicker : public GUIComponentAdapter {
private:
    sf::RectangleShape box;
    sf::CircleShape knob;
    sf::VertexArray colors;
    double hue = 0;

    static double clamp(double n, double min, double max);
public:
    ColorHuePicker();

    static double getHUE(sf::Color c);
    double getCurrentHUE() const;
    void setHUE(double h);
    void setHUE(sf::Color c);

    std::function<void(const sf::Color&)> callBack;
    void setCallBack(std::function<void(const sf::Color&)> cb);

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void onMouseMoved(sf::Vector2f pos);
    virtual void onMousePressed(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_COLORHUEPICKER_H
