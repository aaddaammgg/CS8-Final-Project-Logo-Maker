//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_RICHTEXTFORMAT_H
#define CS008_SFML_TYPING_RICHTEXTFORMAT_H

#include <vector>
#include <SFML/Graphics.hpp>

class RichTextFormat : public sf::Drawable, public sf::Transformable {
private:
    std::vector<sf::Text> texts;
public:
    RichTextFormat();
    RichTextFormat(const sf::String &string);

    RichTextFormat & operator << (const sf::Color &color);
    RichTextFormat & operator << (sf::Text::Style style);
    RichTextFormat & operator << (const sf::String &string);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void eventHandler(sf::RenderWindow& window, sf::Event event);
    void update();
};


#endif //CS008_SFML_TYPING_RICHTEXTFORMAT_H
