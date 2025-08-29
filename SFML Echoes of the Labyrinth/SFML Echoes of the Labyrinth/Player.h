#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "PlayerInput.h"

class Player {
public:
    Player();

    void update(float dt);

    void draw(sf::RenderWindow& window);

    // Getters / Setters
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

private:
    sf::Sprite sprite;       // player sprite
    sf::Vector2f velocity;   // movement Direction
    float speed;        

    sf::RectangleShape shape;
    PlayerInput input;
};


