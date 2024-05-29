//
// Created by Adam G.
// https://en.sfml-dev.org/forums/index.php?topic=19928.0

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceHolder {
private:
    static std::map<std::string, sf::Texture> textures;
    static std::map<std::string, sf::Font> fonts;
    static std::map<std::string, sf::SoundBuffer> sounds;
public:
    static sf::Texture& getTexture(std::string path);
    static sf::Font& getFont(std::string path);
    static sf::SoundBuffer& getSoundBuffer(std::string path);
};


#endif //RESOURCEHOLDER_H
