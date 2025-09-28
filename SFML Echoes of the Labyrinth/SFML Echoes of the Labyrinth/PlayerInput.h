#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @class PlayerInput
 * @brief Handles player input from the keyboard and translates it into movement directions.
 *
 * Supports both WASD and arrow keys.
 */
class PlayerInput {
public:
    /**
     * @brief Returns a normalized 2D direction vector based on current keyboard input.
     * - WASD and arrow keys are supported.
     * - Diagonal movement is normalized so that speed remains consistent.
     *
     * @return sf::Vector2f The movement direction vector.
     */
    sf::Vector2f getInputDirection() const;
};
