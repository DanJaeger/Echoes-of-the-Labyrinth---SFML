#include "Collectable.h"
#include <cmath>  // for std::sin

Collectable::Collectable(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture)
    : body(), collider(&body), collected(false),
    basePosition(position), elapsedTime(0.f),
    floatSpeed(Config::Collectables::FLOAT_SPEED), floatHeight(Config::Collectables::FLOAT_HEIGHT)
{
    body.setSize(size);
    body.setOrigin(size / 2.f);   // center origin
    body.setPosition(position);
    body.setTexture(&texture);
}

// Move constructor
Collectable::Collectable(Collectable&& other) noexcept
    : body(std::move(other.body)), collider(&body), collected(other.collected),
    basePosition(other.basePosition), elapsedTime(other.elapsedTime),
    floatSpeed(other.floatSpeed), floatHeight(other.floatHeight)
{
}

// Move assignment operator
Collectable& Collectable::operator=(Collectable&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);   // rebind collider to the new body
        collected = other.collected;
        basePosition = other.basePosition;
        elapsedTime = other.elapsedTime;
        floatSpeed = other.floatSpeed;
        floatHeight = other.floatHeight;
    }
    return *this;
}

// Update floating animation if not collected
void Collectable::update(float dt) {
    if (!collected) {
        elapsedTime += dt;
        float offsetY = std::sin(elapsedTime * floatSpeed) * floatHeight;
        body.setPosition(basePosition.x, basePosition.y + offsetY);
    }
}

// Draw the collectable only if it hasn't been collected
void Collectable::draw(sf::RenderWindow& window) {
    if (!collected) {
        window.draw(body);
    }
}

// Return reference to the collider
Collider& Collectable::getCollider() {
    return collider;
}

// Check if item has been collected
bool Collectable::isCollected() const {
    return collected;
}

// Mark collectable as collected
void Collectable::collect() {
    collected = true;
}
