#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Represents a floor tile in the labyrinth.
 *
 * The floor is a static rectangle with a repeated texture applied,
 * used to render the walkable areas of the level.
 */
class Floor {
public:
    /// Construct a floor tile with given size, position, and texture
    Floor(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

    // Move semantics (allowed)
    Floor(Floor&& other) noexcept;
    Floor& operator=(Floor&& other) noexcept;

    // Copy semantics (disabled)
    Floor(const Floor&) = delete;
    Floor& operator=(const Floor&) = delete;

    /// Draw the floor tile on the render window
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape body; ///< Rectangle shape representing the floor tile
};
