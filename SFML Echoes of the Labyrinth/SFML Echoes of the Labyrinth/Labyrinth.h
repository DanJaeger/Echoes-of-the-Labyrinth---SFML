#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random> 
#include "Walls.h"
#include "Player.h"
#include "Floor.h"

enum class CellType {
    Empty,
    Wall,
    Goal
};

class Labyrinth {
public:
    Labyrinth();
    void draw(sf::RenderWindow& window);
    void handleCollisions(Player& player);

    void addBorderWalls(float width, float height, float thickness);
    void generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize);
    void generateMazeDFS(size_t rows, size_t cols, sf::Vector2f cellSize);

    void loadTextures();


private:
    const sf::Texture* backgroundTexture;
    sf::Sprite backgroundSprite;

    const sf::Texture* borderTexture;

    const sf::Texture* wallTexture;
    std::vector<Walls> walls;

    const sf::Texture* floorTexture;
    std::vector<Floor> floors;

    std::vector<std::vector<CellType>> grid; //Matrix to represent the labyrinth

    std::mt19937 rng;
};

#endif


