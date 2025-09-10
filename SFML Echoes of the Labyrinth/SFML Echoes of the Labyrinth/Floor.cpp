#include "Floor.h"

Floor::Floor(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body()
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    const_cast<sf::Texture&>(texture).setRepeated(true);
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

}

Floor::Floor(Floor&& other) noexcept
    : body(std::move(other.body))
{
}

Floor& Floor::operator=(Floor&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
    }
    return *this;
}

void Floor::draw(sf::RenderWindow& window) {
    window.draw(body);
}
