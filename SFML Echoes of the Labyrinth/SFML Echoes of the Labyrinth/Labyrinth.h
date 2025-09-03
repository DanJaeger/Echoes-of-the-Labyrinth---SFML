#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Walls.h"
#include "Player.h"

class Labyrinth {
public:
    Labyrinth(const std::string& textureFile, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);
    void handleCollisions(Player& player);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<Walls> walls;
};

#endif


