#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

/**
 * @brief Represents the level's goal (a chest).
 *
 * The goal starts closed and can transition into an opening animation.
 * Once fully opened, the player can "reach" it to trigger a win condition.
 */
enum class GoalState {
    Closed,   ///< Chest is fully closed
    Opening,  ///< Chest is currently animating open
    Opened    ///< Chest is fully opened
};

class Goal {
public:
    /**
     * @brief Construct a goal with given size, position, and textures.
     * @param size Rectangle size of the goal.
     * @param position World position of the goal.
     * @param closedTex Texture used when the goal is closed.
     * @param openTex Texture used when the goal is fully opened.
     */
    Goal(sf::Vector2f size, sf::Vector2f position,
        const sf::Texture& closedTex, const sf::Texture& openTex);

    // Move semantics (allowed)
    Goal(Goal&& other) noexcept;
    Goal& operator=(Goal&& other) noexcept;

    // Copy semantics (disabled)
    Goal(const Goal&) = delete;
    Goal& operator=(const Goal&) = delete;

    /// Update goal state (handles animation and texture changes)
    void update(float dt);

    /// Render the goal to the window
    void draw(sf::RenderWindow& window);

    /// Access the collider for player interactions
    Collider& getCollider();

    /// Start the opening animation if the goal is closed
    void open();

    /// Check if the goal is either opening or fully open
    bool isOpen() const;

    /// Check if the goal is fully opened
    bool isFullyOpen() const;

    /**
     * @brief Check if the player has reached the goal.
     * @param playerCollider The player's collider.
     * @return True if the goal is fully open and the player overlaps it.
     */
    bool playerReached(const Collider& playerCollider) const;

private:
    sf::RectangleShape body;   ///< Rectangle shape representing the goal
    Collider collider;         ///< Collider for collision detection

    const sf::Texture* closedTexture; ///< Texture when closed
    const sf::Texture* openTexture;   ///< Texture when fully open
    Animation openAnim;               ///< Animation sequence for opening

    GoalState state;   ///< Current state of the goal
    bool openState;    ///< Auxiliary flag for open logic
};
