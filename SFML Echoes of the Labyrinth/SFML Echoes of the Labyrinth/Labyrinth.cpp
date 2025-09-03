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

    walls.emplace_back(sf::Vector2f(200.f, 50.f), sf::Vector2f(300.f, 300.f));
    walls.emplace_back(sf::Vector2f(50.f, 200.f), sf::Vector2f(150.f, 150.f));
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

