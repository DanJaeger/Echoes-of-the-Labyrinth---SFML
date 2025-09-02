#include "Walls.h"

Walls::Walls(sf::Vector2f size, sf::Vector2f position) : collider(body)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setFillColor(sf::Color::Blue);
	body.setPosition(position);
}

Collider& Walls::getCollider() {
	return collider;
}

void Walls::draw(sf::RenderWindow& window) {
	window.draw(body);
}