//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_LETTER_H
#define CS008_SFML_TYPING_LETTER_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

class Letter : public sf::Text {
private:
public:
    Letter();
    Letter(const std::string& str);
};


#endif //CS008_SFML_TYPING_LETTER_H
