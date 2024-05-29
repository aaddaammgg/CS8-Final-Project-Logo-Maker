//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_LOGOMAKER_H
#define CS008_SFML_FINALPROJECT_LOGOMAKER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include "GUIComponent.h"
#include "MenuBar.h"
#include "DisplayLogo.h"
#include "TextInput.h"
#include "Slider.h"
#include "DropdownMenu.h"
#include "ColorSelector.h"

class LogoMaker {
private:
    unsigned int WIDTH = 1280 * .8;
    unsigned int HEIGHT = 800 * .83;
    std::string winTitle = "Logo Maker 3000 (ALPHA)";

    sf::RenderWindow renderWindow;
    std::vector<GUIComponent*> components;

    sf::RenderTexture texture;
    sf::Sprite sprite;

    MenuBar menuBar;
    DisplayLogo displayLogo;
    TextInput logoText;

    Slider textOpacity;
    Slider textXAxis;
    Slider textYAxis;
    Slider textRotate;
    Slider textFontSize;

    Slider shadowOpacity;
    Slider shadowXAxis;
    Slider shadowYAxis;
    Slider shadowRotate;
    Slider shadowSkew;

    ColorSelector backgroundColor;
    ColorSelector textColor;

    DropdownMenu fontDropdown;

    void updateMinMax();
    void updateLogo();

    typedef struct {
        std::string title;
        std::string file;
    } FontInfo;

    typedef enum {
        ROBOTO_REGULAR,
        ROBOTO_BOLD,
        OPENSANS_BOLD,
        ORANGE_JUICE,

        LAST_FONT
    } FONTS;

    static FontInfo getFontInfo(int i);

    void saveProject(const std::string& file);
    void loadProject(const std::string& file);

    void draw();
public:
    void run();
};


#endif //CS008_SFML_FINALPROJECT_LOGOMAKER_H
