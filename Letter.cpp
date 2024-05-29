//
// Created by Adam G.
//

#include "Letter.h"

Letter::Letter() : Letter("-") {

}

Letter::Letter(const std::string& str) {
    setFillColor(sf::Color::Black);
    setString(str);
    setFont(ResourceHolder::getFont("Roboto-Regular.ttf"));
}
