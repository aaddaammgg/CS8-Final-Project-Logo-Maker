//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_SLIDER_H
#define CS008_SFML_FINALPROJECT_SLIDER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <iomanip>
#include <sstream>
#include "GUIComponentAdapter.h"
#include "MultiText.h"

class Slider : public GUIComponentAdapter {
private:
    float value = 0;
    float step = 1;
    float min = 0;
    float max = 100;

    int precision = 0;

    sf::Vector2f origPos;

    MultiText label;
    MultiText labelValue;

    sf::RectangleShape box;
    sf::RectangleShape progressBox;
    sf::RectangleShape knob;

    void updatePos();
public:
    Slider();
    Slider(std::string str, float initialValue = 0);

    float getValue() const;
    void setValue(float val);

    float getStep() const;
    void setStep(float x);

    int getPrecision() const;
    void setPrecision(int x);

    void setLabel(std::string str);

    sf::Vector2f getMinMax() const;
    float getMin() const;
    float getMax() const;

    void setMinMax(sf::Vector2f minMax);
    void setMin(float x);
    void setMax(float x);

    std::function<void(const float&)> callBack;
    void setCallBack(std::function<void(const float&)> cb);

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f pos);
    virtual void onMouseMoved(sf::Vector2f pos);
    virtual void onMouseWheelScrolled(sf::Mouse::Wheel wheel, float delta, sf::Vector2f pos);
    virtual void onMousePressed(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onKeyPressed(const sf::Event::KeyEvent& key);

    virtual Snapshot getSnapshot() {};
    virtual void applySnapshot(const Snapshot& snapshot) {};

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event);
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_SLIDER_H
