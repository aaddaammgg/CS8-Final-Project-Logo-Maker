//
// Created by Adam G.
//

#include "Typing.h"

Typing::Typing() {

}

MultiText &Typing::getMultiText() {
    return mt;
}

Snapshot Typing::getSnapshot() {

}

void Typing::applySnapshot(const Snapshot &snapshot) {

}

void Typing::onTextEntered(sf::Uint32 unicode) {
    switch (unicode) {
        case 8: { // backspace
            mt--;
            break;
        }
        case 32 ... 128: { // 32 through 128 // https://en.wikipedia.org/wiki/List_of_Unicode_characters#Control_codes
            char c = static_cast<char>(unicode);
            mt += c;

            if (SyntaxHighlighter::isOperator(std::string(1, c))) {
                mt.back().setFillColor(SyntaxHighlighter::getColor(OPERATOR));
            } else if (SyntaxHighlighter::isNumber(std::string(1, c))) {
                mt.back().setFillColor(SyntaxHighlighter::getColor(NUMBER));
            } else {
                std::list<MultiText::iteratorsBE> temp = mt.split(' ');

                for (auto i : temp) {
                    if (mt.getString(i.begin, i.end) == "left") {
                        mt.setAlignment(MultiText::ALIGN::LEFT);
                        mt.setPosition({0, 0});
                    } else if (mt.getString(i.begin, i.end) == "center") {
                        mt.setAlignment(MultiText::ALIGN::CENTER);
                        mt.setPosition({400 / 2, 0});
                    } else if (mt.getString(i.begin, i.end) == "right") {
                        mt.setAlignment(MultiText::ALIGN::RIGHT);
                        mt.setPosition({400, 0});
                    } else {
                        sf::Color tempColor = SyntaxHighlighter::getColor(mt.getString(i.begin, i.end));
                        if (tempColor != sf::Color::Black) {
                            MultiText::iterator it;
                            for (it = i.begin; it != i.end; it++) {
                                it->setFillColor(tempColor);
                            }
                        }
                    }
                }
            }
//            std::cout << mt.getSize().width << std::endl;

            break;
        }
        default:
            break;
    }
}

void Typing::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
    mt.setCharacterSize(static_cast<unsigned int>(size.y));
}

void Typing::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(mt, states);
}

void Typing::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    GUIComponentAdapter::addEventHandler(window, event);
}

void Typing::update() {
    mt.update();
}
