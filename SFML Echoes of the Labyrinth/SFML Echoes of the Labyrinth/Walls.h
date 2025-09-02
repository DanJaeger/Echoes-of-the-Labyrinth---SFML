#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Walls
{
public:
	Walls(sf::Vector2f size, sf::Vector2f position);

	void draw(sf::RenderWindow& window);

	Collider& getCollider();
private:
	sf::RectangleShape body;

	Collider collider;
};

