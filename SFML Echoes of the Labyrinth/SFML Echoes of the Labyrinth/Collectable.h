#pragma once 
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Config.h"

/**
 * @brief Represents a collectable item in the game world.
 * It floats up and down slightly to draw attention and can be collected by the player.
 */
class Collectable {
public:
    /// Construct a collectable with size, position, and texture
    Collectable(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

    // Move semantics (allowed)
    Collectable(Collectable&& other) noexcept;
    Collectable& operator=(Collectable&& other) noexcept;

    // Copy semantics (disabled)
    Collectable(const Collectable&) = delete;
    Collectable& operator=(const Collectable&) = delete;

    /// Update floating animation and state
    void update(float dt);

    /// Draw the collectable on the window if not collected
    void draw(sf::RenderWindow& window);

    /// Get the collider of the collectable
    Collider& getCollider();

    /// Check if the collectable has already been picked up
    bool isCollected() const;

    /// Mark this collectable as collected (disables rendering & collision)
    void collect();

private:

    sf::RectangleShape body;   ///< The visible shape of the collectable
    Collider collider;         ///< Collider for detecting player interaction
    bool collected;            ///< Flag to indicate if item is collected

    sf::Vector2f basePosition; ///< Base position (floating anim is relative to this)
    float elapsedTime;         ///< Accumulated time for floating animation
    float floatSpeed;          ///< Current floating speed
    float floatHeight;         ///< Current floating height
};
