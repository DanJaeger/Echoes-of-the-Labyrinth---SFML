#include "Collectable.h"

Collectable::Collectable(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body(), collider(&body), collected(false), 
    basePosition(position), elapsedTime(0.f),
    floatSpeed(5.f), floatHeight(2.f)
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    body.setTexture(&texture);
}

Collectable::Collectable(Collectable&& other) noexcept
    : body(std::move(other.body)), collider(&body), collected(other.collected),
    basePosition(other.basePosition), elapsedTime(other.elapsedTime),
    floatSpeed(other.floatSpeed), floatHeight(other.floatHeight)
{
}

Collectable& Collectable::operator=(Collectable&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);
        collected = other.collected;
        basePosition = other.basePosition;
        elapsedTime = other.elapsedTime;
        floatSpeed = other.floatSpeed;
        floatHeight = other.floatHeight;
    }
    return *this;
}

void Collectable::update(float dt) {
    if (!collected) {
        elapsedTime += dt;
        float offsetY = std::sin(elapsedTime * floatSpeed) * floatHeight;
        body.setPosition(basePosition.x, basePosition.y + offsetY);
    }
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
