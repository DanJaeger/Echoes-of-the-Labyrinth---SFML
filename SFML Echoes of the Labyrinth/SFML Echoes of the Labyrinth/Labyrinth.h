#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Walls.h"
#include "Player.h"

enum class CellType {
    Empty,
    WallHorizontal,
    WallVertical,
    Goal
};

class Labyrinth {
public:
    Labyrinth(const std::string& textureFile, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);
    void handleCollisions(Player& player);

    void addBorderWalls(float width, float height, float thickness);
    void generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<Walls> walls;

    std::vector<std::vector<CellType>> grid; //Matrix to represent the labyrinth
};

#endif


