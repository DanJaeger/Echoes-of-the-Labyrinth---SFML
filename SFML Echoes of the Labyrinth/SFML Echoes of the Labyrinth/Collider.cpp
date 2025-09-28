#include "Collider.h"
#include <algorithm> // for std::min, std::max
#include <cmath>     // for std::abs

// Constructor
Collider::Collider(sf::RectangleShape* body)
    : body(body) {
}

// Move the body by a given offset
void Collider::move(float dx, float dy) {
    body->move(dx, dy);
}

// Get the current position of the collider's body
sf::Vector2f Collider::getPosition() const {
    return body->getPosition();
}

// Get half the size of the collider's body
sf::Vector2f Collider::getHalfSize() const {
    return body->getSize() / 2.f;
}

// Rebind collider to another rectangle shape
void Collider::rebind(sf::RectangleShape* newBody) {
    body = newBody;
}

// Detect and resolve collision with another collider
bool Collider::checkCollision(Collider& other, float push) {
    // Clamp push to [0.0f, 1.0f]
    push = std::min(std::max(push, 0.0f), 1.0f);

    // Positions and half-sizes of both colliders
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();

    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    // Differences between centers
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    // Calculate overlap (negative = overlapping)
    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    // Collision occurred if both overlaps are negative
    if (intersectX < 0.0f && intersectY < 0.0f) {
        // Resolve on the axis with smaller overlap
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                move(intersectX * (1.0f - push), 0.0f);
                other.move(-intersectX * push, 0.0f);
            }
            else {
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX * push, 0.0f);
            }
        }
        else {
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);
            }
            else {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);
            }
        }
        return true;
    }

    return false; // No collision
}

// Detect overlap only (no resolution)
bool Collider::overlaps(const Collider& other) const {
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();

    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    return (intersectX < 0.0f && intersectY < 0.0f);
}
