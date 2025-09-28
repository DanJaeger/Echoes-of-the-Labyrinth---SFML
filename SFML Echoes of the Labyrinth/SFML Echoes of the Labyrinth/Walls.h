#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Config.h"

/**
 * @class Walls
 * @brief Represents a static wall object in the game world.
 *
 * - Displays a rectangle textured with a wall pattern.
 * - Provides a Collider for collision detection.
 * - Non-copyable, but movable (supports move semantics).
 */
class Walls {
public:
    /**
     * @brief Constructs a wall with given size, position, and texture.
     * @param size Size of the wall rectangle.
     * @param position World position of the wall (center-based).
     * @param texture Texture to be applied to the wall surface.
     */
    Walls(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

    // Move constructor
    Walls(Walls&& other) noexcept;

    // Move assignment operator
    Walls& operator=(Walls&& other) noexcept;

    // Disable copy constructor and copy assignment
    Walls(const Walls&) = delete;
    Walls& operator=(const Walls&) = delete;

    /**
     * @brief Renders the wall to the given window.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Provides access to the collider for collision handling.
     * @return Reference to the wall's collider.
     */
    Collider& getCollider();

private:
    sf::RectangleShape body; ///< The visible rectangle representing the wall
    Collider collider;       ///< Collider bound to the rectangle for physics/collision
};
