#include "Floor.h"

// Constructor
Floor::Floor(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body()
{
    // Configure size and origin (centered)
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    // Ensure the texture repeats for larger tiles
    const_cast<sf::Texture&>(texture).setRepeated(true);

    // Apply texture and define texture rectangle
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}

// Move constructor
Floor::Floor(Floor&& other) noexcept
    : body(std::move(other.body)) {
}

// Move assignment operator
Floor& Floor::operator=(Floor&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
    }
    return *this;
}

// Draw floor tile
void Floor::draw(sf::RenderWindow& window) {
    window.draw(body);
}
