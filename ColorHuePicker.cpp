//
// Created by Adam G.
//

#include "ColorHuePicker.h"

ColorHuePicker::ColorHuePicker() {
    box.setSize({255, 255});
    box.setFillColor(sf::Color::Black);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);

    knob.setRadius(5);
    knob.setOrigin({5, 5});
    knob.setOutlineThickness(2);
    knob.setOutlineColor(sf::Color(0,0,0,100));

    colors.setPrimitiveType(sf::Points);
    colors.resize(256 * 256);

    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            sf::Vertex &vertex(colors[y * 256 + x]);

            vertex.position.x = (float)(x);
            vertex.position.y = (float)(255 - y);
        }
    }

    setHUE(hue);

    enableState(HIDDEN);
    disableState(DISABLED);
    disableState(SELECTED);
    disableState(CLICKED);
}

double ColorHuePicker::getCurrentHUE() const {
    return hue;
}

void ColorHuePicker::setHUE(double h) {
    hue = h;

    if (hue < 0) {
        hue = 0;
    }
    else if (hue > 1) {
        hue -= (int)hue;
    }

    knob.setPosition({box.getSize().x, -box.getSize().y + box.getSize().y});

    for (unsigned int y = 0; y < 256; ++y) {
        for (unsigned int x = 0; x < 256; ++x) {
            const double s = x / 255.0;
            const double v = y / 255.0;

            const int cs = hue * 6;

            const double f = hue * 6 - cs;
            const double p = v * (1 - s);
            const double q = v * (1 - s * f);
            const double t = v * (1 - s * (1 - f));

            switch (cs) {
                case 0:
                case 6:
                    colors[y * 256 + x].color = sf::Color(v * 255, t * 255, p * 255);
                    break;
                case 1:
                    colors[y * 256 + x].color = sf::Color(q * 255, v * 255, p * 255);
                    break;
                case 2:
                    colors[y * 256 + x].color = sf::Color(p * 255, v * 255, t * 255);
                    break;
                case 3:
                    colors[y * 256 + x].color = sf::Color(p * 255, q * 255, v * 255);
                    break;
                case 4:
                    colors[y * 256 + x].color = sf::Color(t * 255, p * 255, v * 255);
                    break;
                case 5:
                    colors[y * 256 + x].color = sf::Color(v * 255, p * 255, q * 255);
                    break;
                default:
                    colors[y * 256 + x].color = sf::Color(255, 255, 255);
            }
        }
    }
}

double ColorHuePicker::getHUE(sf::Color c) {
    double red = c.r / 255.0;
    double green = c.g / 255.0;
    double blue = c.b / 255.0;

    double min = std::min(std::min(red, green), blue);
    double max = std::max(std::max(red, green), blue);

    if (min == max) {
        return 0;
    }

    double h;

    if (max == red) {
        h = (green - blue) / (max - min);
    } else if (max == green) {
        h = 2.0 + (blue - red) / (max - min);
    } else {
        h = 4.0 + (red - green) / (max - min);
    }

    h *= 60;

    if (h < 0) {
        h += 360;
    }

    return h / 360;
}

void ColorHuePicker::setCallBack(std::function<void(const sf::Color &)> cb) {
    callBack = std::move(cb);
}

void ColorHuePicker::setHUE(sf::Color c) {
    setHUE(getHUE(c));
}

double ColorHuePicker::clamp(double n, double min, double max) {
    return std::max(min, std::min(n, max));
}

void ColorHuePicker::onMouseMoved(sf::Vector2f pos) {
    if (!isEnabled(CLICKED)) {
        return;
    }

    sf::Vector2f point = getTransform().getInverse().transformPoint(pos);

    auto x = (float)clamp(point.x, 0,  box.getSize().x);

    float y = -(point.y) + box.getSize().y;

    y = (float)clamp(y, 0,  box.getSize().y);

    knob.setPosition({x, -y + box.getSize().y});

    if (callBack != nullptr) {
        sf::Color c = colors[y * 256 + x].color;
        callBack(c);
    }
}

void ColorHuePicker::onMousePressed(sf::Mouse::Button button, sf::Vector2f pos) {
    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect boxPosTransform = getTransform().transformRect(boxBounds);

    if (button == sf::Mouse::Left && !isEnabled(CLICKED) && boxPosTransform.contains(pos)) {
        enableState(CLICKED);
        enableState(SELECTED);
        onMouseMoved(pos);
    }
}

void ColorHuePicker::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect boxPosTransform = getTransform().transformRect(boxBounds);

    if (!boxPosTransform.contains(pos) && !isEnabled(CLICKED)) {
        disableState(SELECTED);
    }

    disableState(CLICKED);
}

void ColorHuePicker::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (isEnabled(HIDDEN)) {
        return;
    }

    states.transform *= getTransform();
    window.draw(box, states);
    window.draw(colors, states);
    window.draw(knob, states);
}

void ColorHuePicker::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    if (isEnabled(HIDDEN) || isEnabled(DISABLED)) {
        return;
    }
    GUIComponentAdapter::addEventHandler(window, event);
}

void ColorHuePicker::update() {
    GUIComponentAdapter::update();
}
