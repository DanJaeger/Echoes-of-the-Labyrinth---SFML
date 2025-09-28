#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Handles axis-aligned bounding box (AABB) collision detection and resolution
 * for game objects represented by an sf::RectangleShape.
 */
class Collider {
public:
    /// Construct a collider bound to a given rectangle body
    explicit Collider(sf::RectangleShape* body);

    /// Check and resolve collision with another collider
    /// @param other The other collider
    /// @param push  Value [0.0f - 1.0f] indicating how collision resolution is distributed
    ///              (0 = only this moves, 1 = only other moves, 0.5 = both equally)
    /// @return True if a collision occurred
    bool checkCollision(Collider& other, float push);

    /// Check for overlap without resolution (useful for triggers/pickups)
    /// @param other The other collider
    /// @return True if colliders overlap
    bool overlaps(const Collider& other) const;

    /// Move the collider by an offset
    void move(float dx, float dy);

    /// Get world position of the collider’s body
    sf::Vector2f getPosition() const;

    /// Get half of the collider’s size (used in overlap calculations)
    sf::Vector2f getHalfSize() const;

    /// Rebind this collider to a new rectangle body
    void rebind(sf::RectangleShape* newBody);

private:
    sf::RectangleShape* body; ///< Pointer to the rectangle shape representing this collider
};
