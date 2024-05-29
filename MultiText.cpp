//
// Created by Adam G.
//

#include "MultiText.h"

MultiText::MultiText() {

}

MultiText::PosBounds MultiText::getLastPos() {
    return {letters.back().getPosition(), letters.back().getLocalBounds()};
}

void MultiText::updateAlignment() {
    switch (align) {
        case MultiText::ALIGN::LEFT: {
            setOrigin({0, 0});
            break;
        }
        case MultiText::ALIGN::CENTER: {
            setOrigin({getSize().width / 2, 0});
            break;
        }
        case MultiText::ALIGN::RIGHT: {
            setOrigin({getSize().width, 0});
            break;
        }
    }
}

void MultiText::updatePosition(Letter &l) {
    PosBounds pb = getLastPos();
    pb.pos.x += pb.bounds.width + pb.bounds.left + 2;
    l.setPosition(pb.pos);
}

void MultiText::push(Letter &l) {
    if (isEnabled(RANDOM_COLOR)) {
        l.setFillColor(randomColor());
    } else if (l.getFillColor() == sf::Color::Black) {
        l.setFillColor(sf::Color::White);
    }

    l.setFont(ResourceHolder::getFont(font));
    l.setFillColor(color);
    l.setCharacterSize(characterSize);

    if (!letters.empty()) {
        updatePosition(l);
    }

    letters.push_back(l);
    updateAlignment();
}

sf::Color MultiText::randomColor() {
    return {static_cast<sf::Uint8>((rand() % 255)), static_cast<sf::Uint8>((rand() % 255)),
            static_cast<sf::Uint8>((rand() % 255))};
}

void MultiText::addChar(char c) {
    Letter l(std::string(1, c));
    push(l);
}

void MultiText::addChar(const std::string &str) {
    Letter l(str);
    push(l);
}

void MultiText::addChar(const sf::Text &text) {
    Letter l = (Letter &&) text;
    push(l);
}

sf::Color MultiText::getColor() {
    return color;
}

void MultiText::setColor(sf::Color c) {
    color = c;
    color.a = opacity;
    for (auto &letter: letters) {
        c.a = opacity;
        letter.setFillColor(c);
    }
}

void MultiText::setFont(const std::string& f) {
    font = f;
    for (auto &letter: letters) {
        letter.setFont(ResourceHolder::getFont(font));
    }
}

sf::Uint8 MultiText::getOpacity() const {
    return opacity;
}

void MultiText::setOpacity(sf::Uint8 a) {
    opacity = a;
    color.a = a;
    for (auto &letter: letters) {
        sf::Color newAlpha = letter.getFillColor();
        newAlpha.a = a;
        letter.setFillColor(newAlpha);
    }
}

std::string MultiText::getString() {
    std::string temp;
    for (auto &letter: letters) {
        temp += letter.getString();
    }

    return temp;
}

std::string MultiText::getString(MultiText::iterator begin, MultiText::iterator end) {
    std::string temp;

    MultiText::iterator it;

    for (it = begin; it != end; it++) {
        temp += it->getString();
    }

    return temp;
}

MultiText::iteratorsBE MultiText::find(std::string str, MultiText::iterator startPos, bool &found) {
    iteratorsBE temp;

    auto t = end();
    t--;
    temp.begin = t;
    temp.end = t;

    MultiText::iterator it;
    MultiText::iterator it2;
    for (it = startPos; it != end(); it++) {
        if (it->getString() == str[0]) {
            std::string tempStr; // = std::string(1, str[0]);
            for (it2 = it; it2 != end(); it2++) {
                tempStr += it2->getString();
                if (tempStr == str) {
                    temp.begin = it;
                    temp.end = it2;
                    found = true;
                    return temp;
                }
            }
        }
    }

    return temp;
}

//                                                ┌── split by space
//                                                │
// split list of letters by a character --> "Hello hi" would turn into a list of 2 begin and end iterators
//                                           ^   ^ ^^
//                                           │   │ ││
//                                  begin <──┘   │ ││
//                                        end <──┘ ││
//                                                 ││
//                                        begin <──┘└──> end
//
//                               list output ──>

std::list<MultiText::iteratorsBE> MultiText::split(char c) {
    std::list<iteratorsBE> temp;

    MultiText::iterator it;
    auto another = begin();

    for (it = begin(); it != end(); it++) {
        bool found = false;
        iteratorsBE t = find(std::string(1, c), another, found);

        if (!found) {
            break;
        }

        iteratorsBE main;
        main.begin = another;
        main.end = t.begin;
        another = t.end;
        another++;

        temp.push_back(main);
    }

    iteratorsBE t;
    t.begin = another;
    t.end = end();

    temp.push_back(t);

    return temp;
}

sf::FloatRect MultiText::getSize() {
    sf::FloatRect temp = {0, 0, 0, static_cast<float>(getCharacterSize())};

    if (!isEmpty()) {
        float lastCharX = letters.back().getPosition().x;
        lastCharX += letters.back().getGlobalBounds().width;

        temp.width = lastCharX;
    }

    return temp;
}

unsigned int MultiText::getCharacterSize() const {
    return characterSize;
}

void MultiText::setCharacterSize(unsigned int size) {
    characterSize = size;
    for (auto &letter: letters) {
        letter.setCharacterSize(size);
    }
}

int MultiText::getCharCount() {
    return static_cast<int>(letters.size());
}

MultiText::ALIGN MultiText::getAlignment() {
    return align;
}

void MultiText::setAlignment(MultiText::ALIGN alignment) {
    this->align = alignment;
    updateAlignment();
}

bool MultiText::isEmpty() {
    return letters.empty();
}

void MultiText::removeChar() {
    if (!letters.empty()) {
        letters.pop_back();
        updateAlignment();
    }
}

void MultiText::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto const &letter: letters) {
        window.draw(letter, states);
    }
}

void MultiText::update() {

}

Letter &MultiText::front() {
    return letters.front();
}

Letter &MultiText::back() {
    return letters.back();
}

MultiText::iterator MultiText::begin() {
    return letters.begin();
}

MultiText::iterator MultiText::end() {
    return letters.end();
}

MultiText &MultiText::operator=(const std::string &rhs) {
    this->letters.clear();
    this->addChar(rhs);

    return *this;
}

MultiText &MultiText::operator+=(const char &rhs) {
    this->addChar(rhs);
    return *this;
}

MultiText &MultiText::operator+=(const std::string &rhs) {
    this->addChar(rhs);
    return *this;
}

MultiText &MultiText::operator+=(const sf::Text &rhs) {
    this->addChar(rhs);
    return *this;
}

MultiText &MultiText::operator--() {
    this->removeChar();
    return *this;
}

MultiText MultiText::operator--(int) &{
    MultiText tmp(*this);
    operator--();
    return tmp;
}

//Letter MultiText::operator[](int i) const {
//    return index(i);
//}

//Letter &MultiText::operator[](int i) {
//    return index(i);
//}
