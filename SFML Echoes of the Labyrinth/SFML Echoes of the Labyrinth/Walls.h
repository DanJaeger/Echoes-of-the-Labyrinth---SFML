#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Walls
{
public:
	Walls(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

	Walls(Walls&& other) noexcept;
	Walls& operator=(Walls&& other) noexcept;

	Walls(const Walls&) = delete;
	Walls& operator=(const Walls&) = delete;

	void draw(sf::RenderWindow& window);
	Collider& getCollider();

private:
	sf::RectangleShape body;
	Collider collider;
};

