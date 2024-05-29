//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_MULTITEXT_H
#define CS008_SFML_TYPING_MULTITEXT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Letter.h"
#include "States.h"

class MultiText : public sf::Drawable, public sf::Transformable, public States {
public:
    typedef struct {
        sf::Vector2f pos;
        sf::FloatRect bounds;
    } PosBounds;

    typedef std::list<Letter>::iterator iterator;

    typedef struct {
        MultiText::iterator begin;
        MultiText::iterator end;
    } iteratorsBE;

    typedef enum {
        LEFT,
        CENTER,
        RIGHT
    } ALIGN;

private:
    std::list<Letter> letters;
    unsigned int characterSize = 30;
    sf::Uint8 opacity = 255;
    sf::Color color = sf::Color::White;
    std::string font = "Roboto-Regular.ttf";
    MultiText::ALIGN align = MultiText::ALIGN::LEFT;

    void updateAlignment();
    PosBounds getLastPos();
    void updatePosition(Letter& l);
    void push(Letter& l);
    static sf::Color randomColor();

public:
    MultiText();

    void addChar(char c);
    void addChar(const std::string& str);
    void addChar(const sf::Text& text);

    std::string getString();
    std::string getString(MultiText::iterator begin, MultiText::iterator end);

    std::list<iteratorsBE> split(char c);
    iteratorsBE find(std::string str, MultiText::iterator startPos, bool& found);

//    MultiText::iteratorsBE getBeginEnd;

    sf::FloatRect getSize();
    unsigned int getCharacterSize() const;
    void setCharacterSize(unsigned int size);
    int getCharCount();

    sf::Color getColor();
    void setColor(sf::Color c);

    void setFont(const std::string& f);

    sf::Uint8 getOpacity() const;
    void setOpacity(sf::Uint8 a);

    MultiText::ALIGN getAlignment();
    void setAlignment(MultiText::ALIGN alignment);

    bool isEmpty();

    void removeChar();

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void update();

    Letter& front();
    Letter& back();

    MultiText::iterator begin(); // begin iterator
    MultiText::iterator end(); // end iterator


    MultiText& operator=(const std::string& rhs);
    MultiText& operator+=(const char& rhs);
    MultiText& operator+=(const std::string& rhs);
    MultiText& operator+=(const sf::Text& rhs);
    MultiText& operator--();
    MultiText operator--(int)&;
};


#endif //CS008_SFML_TYPING_MULTITEXT_H
