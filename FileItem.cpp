//
// Created by Adam G.
//

#include "FileItem.h"

FileItem::FileItem() {

}

FileItem::FileItem(Image::imageType icon, std::string text, sf::Vector2f size, sf::Vector2f position) {

}

void FileItem::setIcon(Image::imageType icon) {
    this->icon.setTexture(Image::getTexture(icon));
}

void FileItem::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    Item::draw(window, states);
}

void FileItem::update() {
    Item::update();
}
