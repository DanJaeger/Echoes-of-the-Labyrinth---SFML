#include "Labyrinth.h"
#include "ResourceManager.h"
#include <iostream>

Labyrinth::Labyrinth(const std::string& textureFile, const sf::Vector2u& windowSize) {
    texture = ResourceManager::getInstance().getTexture(textureFile);
    sprite.setTexture(texture);

    // Fixes background texture size
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    // Center texture
    sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void Labyrinth::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    for (auto& wall : walls)
        wall.draw(window);
}

void Labyrinth::handleCollisions(Player& player)
{
    for (auto& wall : walls) {
        player.getCollider().checkCollision(wall.getCollider(), 0.0f);
    }
}

void Labyrinth::addBorderWalls(float width, float height, float thickness)
{

    //walls.clear();

    // TOP
    walls.emplace_back(
        sf::Vector2f(width, thickness),              // width = whole level, altitude = thickness
        sf::Vector2f(width / 2.f, thickness / 2.f)   // up center
    );

    // BOTTOM
    walls.emplace_back(
        sf::Vector2f(width, thickness),
        sf::Vector2f(width / 2.f, height - thickness / 2.f)
    );

    // LEFT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(thickness / 2.f, height / 2.f)
    );

    // RIGHT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(width - thickness / 2.f, height / 2.f)
    );
}

void Labyrinth::generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize)
{
    grid = layout;
    walls.clear();

    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            sf::Vector2f pos(
                col * cellSize.x + cellSize.x / 2.f,
                row * cellSize.y + cellSize.y / 2.f
            );

            switch (grid[row][col]) {
            case CellType::WallHorizontal: {
                sf::Vector2f size(cellSize.x, cellSize.y * 0.2f);
                walls.emplace_back(size, pos);
                break;
            }
            case CellType::WallVertical: {
                sf::Vector2f size(cellSize.x * 0.2f, cellSize.y);
                walls.emplace_back(size, pos);
                break;
            }
            case CellType::Goal: {
                // TODO
                break;
            }
            default:
                break;
            }
        }
    }
}

