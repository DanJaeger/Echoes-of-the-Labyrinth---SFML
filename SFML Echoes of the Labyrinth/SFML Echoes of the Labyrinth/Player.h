#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "PlayerInput.h"
#include "Collider.h"
#include "Animation.h"

/**
 * @class Player
 * @brief Represents the player character with movement, collision, and animations.
 *
 * The Player is defined by:
 * - A hitbox used for physics and collision.
 * - A sprite used for rendering.
 * - Idle and walking animations.
 * - Input handling for movement.
 */
class Player {
public:
    Player();

    void update(float dt);                ///< Updates movement, position, and animations.
    void draw(sf::RenderWindow& window);  ///< Renders the player sprite to the screen.

    // Getters / Setters
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    Collider& getCollider();

private:
    // Initialization helpers
    void initHitbox();
    void initSprite();
    void initAnimation();

    // Update helpers
    void updateAnimation(sf::Vector2f velocity, float dt);
    void moveSpriteWithHitbox();

    // Rendering
    sf::Sprite sprite;

    // Movement
    sf::Vector2f velocity;
    float speed;

    // Collision
    sf::RectangleShape hitbox;
    Collider collider;

    // Input
    PlayerInput input;

    // Animations
    Animation idleAnim;
    Animation walkAnim;
    Animation* currentAnim;

    // Direction & scaling
    bool faceRight;
    sf::Vector2f baseScale;
};
