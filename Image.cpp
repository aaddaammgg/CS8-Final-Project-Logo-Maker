//
// Created by Adam G.
//

#include "Image.h"

sf::Texture &Image::getTexture(Image::imageType icon) {
    switch (icon) {
        case DIRECTORY:
            return ResourceHolder::getTexture("images/directory.png");
        case FILE:
            return ResourceHolder::getTexture("images/file.png");
        default:
            return ResourceHolder::getTexture("images/error.png");
    }
}
