#include "Walls.h"

Walls::Walls(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body(), collider(&body) // Initialize collider bound to the rectangle
{
    // Configure the rectangle shape
    body.setSize(size);
    body.setOrigin(size / 2.f); // Center origin for easier positioning
    body.setPosition(position);

    // Ensure the texture is set to repeat (useful for large walls)
    const_cast<sf::Texture&>(texture).setRepeated(true);
    body.setTexture(&texture);

    // Define the visible texture region (from Config constants)
    body.setTextureRect(sf::IntRect(
        Config::Walls::TEXTURE_OFFSET_X,
        Config::Walls::TEXTURE_OFFSET_Y,
        texture.getSize().x,
        texture.getSize().y
    ));
}

Walls::Walls(Walls&& other) noexcept
    : body(std::move(other.body)), collider(&body) {
    // Collider is rebound to the new body after move
}

Walls& Walls::operator=(Walls&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body); // Rebind collider to new body
    }
    return *this;
}

void Walls::draw(sf::RenderWindow& window) {
    window.draw(body);
}

Collider& Walls::getCollider() {
    return collider;
}
