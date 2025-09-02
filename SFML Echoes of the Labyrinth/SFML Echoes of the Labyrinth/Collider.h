#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);

    bool checkCollision(Collider& other, float push);
    void move(float dx, float dy);

    // Getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getHalfSize() const;

private: 
    sf::RectangleShape& body;
};

