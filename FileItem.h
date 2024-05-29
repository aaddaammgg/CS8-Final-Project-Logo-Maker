//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_FILEITEM_H
#define CS008_SFML_FINALPROJECT_FILEITEM_H

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Image.h"

class FileItem : public Item {
private:
    sf::Sprite icon;
    float padding = 5;
public:
    FileItem();
    FileItem(Image::imageType icon, std::string text, sf::Vector2f size, sf::Vector2f position);

    void setIcon(Image::imageType icon);

    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void update();
};


#endif //CS008_SFML_FINALPROJECT_FILEITEM_H
