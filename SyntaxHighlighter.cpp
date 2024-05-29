//
// Created by Adam G.
//

#include "SyntaxHighlighter.h"

std::map<std::string, bool> SyntaxHighlighter::dataTypes = {
        {"int", true},
        {"char", true},
        {"double", true},
        {"bool", true},
        {"void", true},
        {"float", true}
};

bool SyntaxHighlighter::isNumber(const std::string &str) {
    std::string::const_iterator it = str.begin();

    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }

    return !str.empty() && it == str.end();
}

bool SyntaxHighlighter::isOperator(const std::string &str) {
    char c = str[0];

    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

bool SyntaxHighlighter::isDataType(const std::string &str) {
    return dataTypes[str];
}

sf::Color SyntaxHighlighter::getColor(SyntaxColor color) {
    switch (color) {
        case NUMBER:
            return sf::Color::Red;
        case OPERATOR:
            return sf::Color::Green;
        case DATATYPE:
            return sf::Color::Blue;
        default:
            return sf::Color::Black;
    }
}

sf::Color SyntaxHighlighter::getColor(std::string str) {
    if (isDataType(str)) {
        return getColor(DATATYPE);
    }

    return sf::Color::Black;
}
