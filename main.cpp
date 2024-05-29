#include <iostream>
#include <SFML/Graphics.hpp>
#include "LogoMaker.h"

int main() {
    srand(time(nullptr));
    sf::err().rdbuf(nullptr);

    LogoMaker logoMaker;
    logoMaker.run();

    return 0;
}