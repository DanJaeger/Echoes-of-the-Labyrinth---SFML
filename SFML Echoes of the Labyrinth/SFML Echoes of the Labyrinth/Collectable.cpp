#include "Collectable.h"

Collectable::Collectable(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body(), collider(&body), collected(false)
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    body.setTexture(&texture);
}

Collectable::Collectable(Collectable&& other) noexcept
    : body(std::move(other.body)), collider(&body), collected(other.collected)
{
}

Collectable& Collectable::operator=(Collectable&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);
        collected = other.collected;
    }
    return *this;
}

void Collectable::draw(sf::RenderWindow& window) {
    if (!collected) {
        window.draw(body);
    }
}

Collider& Collectable::getCollider() {
    return collider;
}

bool Collectable::isCollected() const {
    return collected;
}

void Collectable::collect() {
    collected = true;
}
