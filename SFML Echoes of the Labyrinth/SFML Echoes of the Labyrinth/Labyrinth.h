#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random> 
#include <optional>
#include <functional>
#include "Walls.h"
#include "Player.h"
#include "Floor.h"
#include "Collectable.h"
#include "Goal.h"

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

    void generate(sf::Vector2u windowSize, unsigned cellPixelSize = 32);
    void reset(sf::Vector2u windowSize);

    sf::Vector2f getSpawnPoint() const; 

    void setOnWin(std::function<void()> callback);

private:
    void addBorderWalls(float width, float height, float thickness);
    void generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize);
    void generateMazeDFS(size_t rows, size_t cols, sf::Vector2f cellSize);

    void loadTextures();

    const sf::Texture* backgroundTexture;
    sf::Sprite backgroundSprite;

    const sf::Texture* borderTexture;

    const sf::Texture* wallTexture;
    std::vector<Walls> walls;

    const sf::Texture* floorTexture;
    std::vector<Floor> floors;

    const sf::Texture* collectableTexture;
    std::vector<Collectable> collectables;

    const sf::Texture* goalClosedTexture;
    const sf::Texture* goalOpenTexture;
    std::optional<Goal> goal;

    std::vector<std::vector<CellType>> grid; //Matrix to represent the labyrinth

    std::mt19937 rng;

    size_t rows;
    size_t cols;
    sf::Vector2f cellSize;

    int numberOfCollectables;

    std::function<void()> onWin;
};

#endif


