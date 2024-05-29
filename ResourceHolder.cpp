//
// Created by Adam G.
// https://en.sfml-dev.org/forums/index.php?topic=19928.0

#include "ResourceHolder.h"

std::map<std::string, sf::Texture> ResourceHolder::textures;
std::map<std::string, sf::Font> ResourceHolder::fonts;
std::map<std::string, sf::SoundBuffer> ResourceHolder::sounds;

sf::Texture &ResourceHolder::getTexture(std::string path) {
    const auto &pairFound = textures.find(path);
    if (pairFound != textures.end()) {
        return pairFound->second;
    } else {
        auto& texture = textures[path];
        texture.loadFromFile(path);
        return texture;
    }
}

sf::Font &ResourceHolder::getFont(std::string path) {
    const auto &pairFound = fonts.find(path);
    if (pairFound != fonts.end()) {
        return pairFound->second;
    } else {
        auto& font = fonts[path];
        font.loadFromFile(path);
        return font;
    }
}

sf::SoundBuffer &ResourceHolder::getSoundBuffer(std::string path) {
    const auto &pairFound = sounds.find(path);
    if (pairFound != sounds.end()) {
        return pairFound->second;
    } else {
        auto& sound = sounds[path];
        sound.loadFromFile(path);
        return sound;
    }
}
