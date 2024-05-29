//
// Created by Adam G.
//

#include "LogoMaker.h"

void LogoMaker::run() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    renderWindow.create({WIDTH, HEIGHT, 32}, winTitle, sf::Style::Default, settings);
    renderWindow.setFramerateLimit(60);
    renderWindow.setVerticalSyncEnabled(false);

    MenuItem menuFile("File");
    menuFile.setSize({250, 50});
    menuFile.addItem("New Project", [&](const std::string& str) {
        std::cout << str << std::endl;
        loadProject("Projects/new.txt");
    });
    menuFile.addItem("Load Project", [&](const std::string& str) {
        std::cout << str << std::endl;
        loadProject("Projects/settings.txt");
    });
    menuFile.addItem("Save Project", [&](const std::string& str) {
        std::cout << str << std::endl;
        saveProject("Projects/settings.txt");
    });
    menuFile.addItem("Exit", [&](const std::string& str) {
        std::cout << str << std::endl;
        renderWindow.close();
    });

    MenuItem menuEdit("Edit");
    menuEdit.setSize({250, 50});
    menuEdit.addItem("Exit", [&](const std::string& str) {
        std::cout << str << std::endl;
        std::cout << sf::Color::Black.toInteger() << std::endl;
//        renderWindow.close();
    });

    MenuItem menuRender("Render");
    menuRender.setSize({250, 50});
    menuRender.addItem("Export", [&](const std::string& str) {
        std::cout << str << std::endl;
        sf::Image img = texture.getTexture().copyToImage();
        img.saveToFile("Exports/Logo.png");
    });

    menuBar.addItem(menuFile);
    menuBar.addItem(menuEdit);
    menuBar.addItem(menuRender);

    displayLogo.setPosition(0, 0);
    displayLogo.setSize({static_cast<float>(WIDTH), 300});
    texture.create(displayLogo.getSize().x, displayLogo.getSize().y);
    sprite.setPosition(0, 55);
    sprite.setTexture(texture.getTexture());

    logoText.setLabel("Text: ");
    logoText.setLabelSize(29);
    logoText.setLabelColor(sf::Color::White);

    sf::Vector2f lastPosition = sprite.getPosition();
    sf::Vector2f lastSize = displayLogo.getSize();

    logoText.setSize({static_cast<float>(WIDTH) - 25, 30});
    logoText.setPosition(10, lastPosition.y + lastSize.y + 15);

    logoText.setCallBack([&](const std::string& str, const bool& isDelete) {
        displayLogo.getLogo() = str;
        displayLogo.getShadow() = str;
        updateMinMax();
    });

    lastPosition = logoText.getPosition();
    lastSize = logoText.getSize();

    float sliderWidth = static_cast<float>(WIDTH / 2.0) - 20 - 50;
    float sliderHeight = 10;

    textOpacity.setLabel("Text Opacity");
    textOpacity.setPosition({10, lastPosition.y + lastSize.y + 15});
    textOpacity.setSize({sliderWidth, sliderHeight});
    textOpacity.setMinMax({0, 255});
    textOpacity.setCallBack([&](const float& value) {
        displayLogo.getLogo().setOpacity(value);
    });
    textOpacity.setValue(255);

    lastPosition = textOpacity.getPosition();
    lastSize = textOpacity.getSize();

    textXAxis.setLabel("Text X-Axis");
    textXAxis.setPosition({10, lastPosition.y + lastSize.y + 15});
    textXAxis.setSize({sliderWidth, sliderHeight});
    textXAxis.setMinMax({0, displayLogo.getSize().x});

    lastPosition = textXAxis.getPosition();
    lastSize = textXAxis.getSize();

    textYAxis.setLabel("Text Y-Axis");
    textYAxis.setPosition({10, lastPosition.y + lastSize.y + 15});
    textYAxis.setSize({sliderWidth, sliderHeight});
    textYAxis.setMinMax({0, displayLogo.getSize().y});

    lastPosition = textYAxis.getPosition();
    lastSize = textYAxis.getSize();

    sliderWidth = static_cast<float>(WIDTH) - 20 - 50;

    textRotate.setLabel("Text Rotation");
    textRotate.setPosition({10, lastPosition.y + lastSize.y + 15});
    textRotate.setSize({sliderWidth, sliderHeight});
    textRotate.setMinMax({0, 360});
    textRotate.setCallBack([&](const float& value) {
        displayLogo.getLogo().setRotation(value);
    });

    lastPosition = textRotate.getPosition();
    lastSize = textRotate.getSize();

    textFontSize.setLabel("Text Font Size");
    textFontSize.setPosition({10, lastPosition.y + lastSize.y + 15});
    textFontSize.setSize({sliderWidth, sliderHeight});
    textFontSize.setMinMax({6, 128});
    textFontSize.setCallBack([&](const float& value) {
        displayLogo.getLogo().setCharacterSize(value);
        displayLogo.getShadow().setCharacterSize(value);
        updateMinMax();
    });

    textFontSize.setValue(64);

    lastPosition = textFontSize.getPosition();
    lastSize = textFontSize.getSize();

    shadowOpacity.setLabel("Shadow Opacity");
    shadowOpacity.setPosition({10, lastPosition.y + lastSize.y + 15});
    shadowOpacity.setSize({sliderWidth, sliderHeight});
    shadowOpacity.setMinMax({0, 255});
    shadowOpacity.setCallBack([&](const float& value) {
        displayLogo.getShadow().setOpacity(value);
    });
    shadowOpacity.setValue(0);

    lastPosition = shadowOpacity.getPosition();
    lastSize = shadowOpacity.getSize();

    shadowXAxis.setLabel("Shadow X-Axis");
    shadowXAxis.setPosition({10, lastPosition.y + lastSize.y + 15});
    shadowXAxis.setSize({sliderWidth, sliderHeight});
    shadowXAxis.setMinMax({0, displayLogo.getSize().x});

    lastPosition = shadowXAxis.getPosition();
    lastSize = shadowXAxis.getSize();

    shadowYAxis.setLabel("Shadow Y-Axis");
    shadowYAxis.setPosition({10, lastPosition.y + lastSize.y + 15});
    shadowYAxis.setSize({sliderWidth, sliderHeight});
    shadowYAxis.setMinMax({0, displayLogo.getSize().y});

    lastPosition = shadowYAxis.getPosition();
    lastSize = shadowYAxis.getSize();

    shadowRotate.setLabel("Shadow Rotation");
    shadowRotate.setPosition({10, lastPosition.y + lastSize.y + 15});
    shadowRotate.setSize({sliderWidth, sliderHeight});
    shadowRotate.setMinMax({0, 360});
    shadowRotate.setCallBack([&](const float& value) {
        displayLogo.getShadow().setRotation(value);
    });

    lastPosition = shadowRotate.getPosition();
    lastSize = shadowRotate.getSize();

    shadowSkew.setLabel("Shadow Skew");
    shadowSkew.setPosition({10, lastPosition.y + lastSize.y + 15});
    shadowSkew.setSize({sliderWidth, sliderHeight});
    shadowSkew.setMinMax({-3, 3});
    shadowSkew.setPrecision(3);
    shadowSkew.setStep(.025);
    shadowSkew.setCallBack([&](const float& value) {
        displayLogo.getShadow().setScale({1, value});
        updateMinMax();
    });
    shadowSkew.setValue(-3);

    lastPosition = textOpacity.getPosition();
    lastSize = textOpacity.getSize();

    fontDropdown.setSize({static_cast<float>(WIDTH / 2.0) - 15, 45});
    fontDropdown.setPosition({lastSize.x + 70, lastPosition.y - lastSize.y + 17});

    for (int i = 0; i < LAST_FONT; i++) {
        fontDropdown.addItem(getFontInfo(i).title);
    }

    fontDropdown.setCallBack([&](const int& index) {
        std::string font = getFontInfo(index).file;

        displayLogo.getLogo().setFont(font);
        displayLogo.getShadow().setFont(font);
    });

    lastPosition = fontDropdown.getPosition();
    lastSize = fontDropdown.getSize();

    textColor.setLabel("Text:");
    textColor.setPosition({(float)(WIDTH * .5), 6});
    textColor.setCallBack([&](const sf::Color& color) {
        displayLogo.getLogo().setColor(color);
        displayLogo.getShadow().setColor(color);
    });

    backgroundColor.setLabel("Background:");
    backgroundColor.setPosition({(float)(WIDTH * .7), 6});
    backgroundColor.setCallBack([&](const sf::Color& color) {
        displayLogo.getBox().setFillColor(color);
    });

    components.push_back(&textColor);
    components.push_back(&backgroundColor);


    components.push_back(&shadowSkew);
    components.push_back(&shadowYAxis);
    components.push_back(&shadowXAxis);
    components.push_back(&shadowRotate);
    components.push_back(&shadowOpacity);

//    components.push_back(&textColor);
    components.push_back(&textFontSize);
    components.push_back(&textYAxis);
    components.push_back(&textXAxis);
    components.push_back(&textRotate);
    components.push_back(&textOpacity);

//    components.push_back(&backgroundColor);
    components.push_back(&fontDropdown);
    components.push_back(&logoText);

    components.push_back(&menuBar);

    bool isEvent = false;

    while (renderWindow.isOpen()) {
        sf::Event event{};
        while (renderWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    renderWindow.close();
                    break;
                case sf::Event::Resized: {
                    unsigned int newWIDTH = event.size.width;
                    unsigned int newHEIGHT = event.size.height;

                    if (WIDTH * newHEIGHT > newWIDTH * HEIGHT) {
                        newHEIGHT = (newWIDTH * HEIGHT) / WIDTH;
                    } else {
                        newWIDTH = (newHEIGHT * WIDTH) / HEIGHT;
                    }

                    renderWindow.setSize({newWIDTH, newHEIGHT});
                    break;
                }
            }

            isEvent = true;

            updateLogo();

            for (auto & component : components) {
                component->addEventHandler(renderWindow, event);
            }
            draw();
        }

        if (!isEvent) {
            draw();
        }
        
        isEvent = false;
    }
}

void LogoMaker::updateMinMax() {
    sf::FloatRect logoBounds = displayLogo.getLogo().getSize();
    sf::FloatRect shadowBounds = displayLogo.getShadow().getSize();

    textXAxis.setMax(displayLogo.getSize().x - logoBounds.width);
    textYAxis.setMax(displayLogo.getSize().y - logoBounds.height);
    shadowXAxis.setMax(displayLogo.getSize().x - shadowBounds.width);
    shadowYAxis.setMax(displayLogo.getSize().y + shadowBounds.height);
}

void LogoMaker::updateLogo() {
    displayLogo.getLogo().setPosition({textXAxis.getValue(), textYAxis.getValue()});
    displayLogo.getShadow().setPosition({shadowXAxis.getValue(), shadowYAxis.getValue()});
}

LogoMaker::FontInfo LogoMaker::getFontInfo(int i) {
    switch ((FONTS) i) {
        case ROBOTO_REGULAR:
            return {"Roboto Regular", "Roboto-Regular.ttf"};
        case ROBOTO_BOLD:
            return {"Roboto Bold", "Roboto-Bold.ttf"};
        case OPENSANS_BOLD:
            return {"OpenSans Bold", "OpenSans-Bold.ttf"};
        case ORANGE_JUICE:
            return {"Orange Juice", "Orange-Juice.ttf"};
        default:
            return {"NULL", "NULL"};
    }
}

void LogoMaker::saveProject(const std::string& file) {
    std::ofstream fout;

    fout.open(file);

    if (fout.fail()) {
        std::cout << "Cannot save project: " << file << std::endl;
        return;
    }

    fout << (std::string) logoText.getString() << std::endl;

    fout << textOpacity.getValue() << std::endl;
    fout << textXAxis.getValue() << std::endl;
    fout << textYAxis.getValue() << std::endl;
    fout << textRotate.getValue() << std::endl;
    fout << textFontSize.getValue() << std::endl;

    fout << shadowOpacity.getValue() << std::endl;
    fout << shadowXAxis.getValue() << std::endl;
    fout << shadowYAxis.getValue() << std::endl;
    fout << shadowRotate.getValue() << std::endl;
    fout << shadowSkew.getValue() << std::endl;

    fout << displayLogo.getBox().getFillColor().toInteger() << std::endl;
    fout << displayLogo.getLogo().getColor().toInteger() << std::endl;

    fout << fontDropdown.getIndex() << std::endl;

    fout.close();
}

void LogoMaker::loadProject(const std::string& file) {
    std::ifstream fin;

    fin.open(file);

    if (fin.fail()) {
        std::cout << "Cannot load project: " << file << std::endl;
        return;
    }

    std::string textStr;
    sf::Vector2f pos;
    float x;

    fin >> textStr;
    fin >> x;
    fin >> pos.x;
    fin >> pos.y;

    logoText.setString(textStr);
    displayLogo.getLogo() = textStr;
    displayLogo.getShadow() = textStr;

    textOpacity.setValue(x);
    textXAxis.setValue(pos.x);
    textYAxis.setValue(pos.y);

    fin >> x;
    textRotate.setValue(x);

    fin >> x;
    textFontSize.setValue(x);

    fin >> x;
    fin >> pos.x;
    fin >> pos.y;

    shadowOpacity.setValue(x);
    shadowXAxis.setValue(pos.x);
    shadowYAxis.setValue(pos.y);

    fin >> x;
    shadowRotate.setValue(x);

    fin >> x;
    shadowSkew.setValue(x);

    updateLogo();

    sf::Uint32 color;

    fin >> color;
    displayLogo.getBox().setFillColor(sf::Color(color));
    fin >> color;
    displayLogo.getLogo().setColor(sf::Color(color));
    displayLogo.getShadow().setColor(sf::Color(color));

    fin >> x;
    fontDropdown.setIndex((int)x);


    fin.close();
}

void LogoMaker::draw() {
    for (auto & component : components) {
        component->update();
    }

    displayLogo.update();

    texture.clear(sf::Color::Black);
    texture.draw(displayLogo);
    texture.display();

    renderWindow.clear(sf::Color(sf::Color::Black));
    renderWindow.draw(sprite);

    for (auto & component : components) {
        renderWindow.draw(*component);
    }

    renderWindow.display();
}