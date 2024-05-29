//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_SYNTAXHIGHLIGHTER_H
#define CS008_SFML_TYPING_SYNTAXHIGHLIGHTER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum SyntaxColor {
    NUMBER, OPERATOR, DATATYPE,

    LAST_SYNTAXCOLOR
};

class SyntaxHighlighter {

private:
    static std::map<std::string, bool> dataTypes;
public:
    static sf::Color getColor(std::string str);
    static bool isNumber(const std::string& str);
    static bool isOperator(const std::string& str);
    static bool isDataType(const std::string& str);
    static sf::Color getColor(SyntaxColor color);
};


#endif //CS008_SFML_TYPING_SYNTAXHIGHLIGHTER_H
