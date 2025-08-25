#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>

class Labyrinth {
public:
    Labyrinth(const std::string& textureFile, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif


