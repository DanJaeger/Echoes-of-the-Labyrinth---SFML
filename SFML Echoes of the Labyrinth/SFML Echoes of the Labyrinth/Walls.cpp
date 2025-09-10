#include "Walls.h"

Walls::Walls(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body(), collider(&body) // collider pointing to body
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    const_cast<sf::Texture&>(texture).setRepeated(true);
    body.setTexture(&texture);

    body.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}

Walls::Walls(Walls&& other) noexcept
    : body(std::move(other.body)), collider(&body) {
}

Walls& Walls::operator=(Walls&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);
    }
    return *this;
}

void Walls::draw(sf::RenderWindow& window) {
    window.draw(body);
}

Collider& Walls::getCollider() {
	return collider;
}
