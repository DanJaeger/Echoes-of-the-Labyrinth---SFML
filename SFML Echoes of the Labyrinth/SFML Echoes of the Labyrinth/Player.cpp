#include "Player.h"
#include "Config.h"
#include <cmath>
#include "GameTimer.h"

Player::Player()
    : hitbox(),
    collider(&hitbox),
    idleAnim(Config::Player::IDLE_FRAME_TIME),
    walkAnim(Config::Player::WALK_FRAME_TIME),
    faceRight(true),
    baseScale(Config::Player::BASE_SCALE)
{
    initHitbox();      // Setup hitbox size, color, and position
    initSprite();      // Setup sprite scale and alignment
    initAnimation();   // Load animation frames

    speed = Config::Player::SPEED;
}

/**
 * @brief Updates the player's position and animation each frame.
 * @param dt Delta time in seconds.
 */
void Player::update(float dt) {
    // Get input direction from keyboard
    velocity = input.getInputDirection();

    // Move the hitbox according to velocity and speed
    hitbox.move(velocity * speed * dt);

    // Update animation based on movement state
    updateAnimation(velocity, dt);

    // Sync sprite position with hitbox position
    moveSpriteWithHitbox();
}

/**
 * @brief Handles animation switching and updating based on velocity.
 */
void Player::updateAnimation(sf::Vector2f velocity, float dt) {
    // Determine animation state
    if (velocity.x != 0.f || velocity.y != 0.f) {
        if (currentAnim != &walkAnim) {
            currentAnim = &walkAnim;
            currentAnim->reset();
        }
        // Flip sprite depending on horizontal direction
        if (velocity.x < 0.f) faceRight = false;
        else if (velocity.x > 0.f) faceRight = true;
    }
    else {
        if (currentAnim != &idleAnim) {
            currentAnim = &idleAnim;
            currentAnim->reset();
        }
    }

    // Update current animation frame
    currentAnim->update(dt);
    sprite.setTexture(currentAnim->getCurrentTexture(), false);

    // Apply sprite flip if facing left
    if (faceRight) {
        sprite.setScale(baseScale.x, baseScale.y);
    }
    else {
        sprite.setScale(-baseScale.x, baseScale.y);
    }
}

/**
 * @brief Aligns the sprite to follow the hitbox center.
 */
void Player::moveSpriteWithHitbox() {
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.f,
        sprite.getLocalBounds().height / 1.5f
    );
    sprite.setPosition(hitbox.getPosition());
}

/**
 * @brief Renders the player sprite to the screen.
 */
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    // Debug: window.draw(hitbox);
}

/**
 * @brief Accessor for collider reference.
 */
Collider& Player::getCollider() {
    return collider;
}

/**
 * @brief Get current player position.
 */
sf::Vector2f Player::getPosition() const {
    return hitbox.getPosition();
}

/**
 * @brief Set player position manually.
 */
void Player::setPosition(const sf::Vector2f& pos) {
    hitbox.setPosition(pos);
    sprite.setPosition(pos);
}

/**
 * @brief Initialize hitbox shape (size, color, origin, position).
 */
void Player::initHitbox() {
    hitbox.setSize(Config::Player::HITBOX_SIZE);
    hitbox.setFillColor(Config::Player::HITBOX_FILL);
    hitbox.setOutlineColor(Config::Player::HITBOX_OUTLINE); // Debug visualization
    hitbox.setOutlineThickness(Config::Player::HITBOX_OUTLINE_THICKNESS);
    hitbox.setOrigin(hitbox.getSize() / 2.f);
    hitbox.setPosition(Config::Player::START_POSITION);
}

/**
 * @brief Setup sprite origin, position, and scale.
 */
void Player::initSprite() {
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.f,
        sprite.getLocalBounds().height / 1.5f
    );
    sprite.setPosition(hitbox.getPosition());
    sprite.setScale(baseScale);
}

/**
 * @brief Load idle and walking animations from Config.
 */
void Player::initAnimation() {
    // Idle animation
    for (const auto& frame : Config::Player::IDLE_FRAMES) {
        idleAnim.addFrame(frame);
    }

    // Walking animation
    for (const auto& frame : Config::Player::WALK_FRAMES) {
        walkAnim.addFrame(frame);
    }

    // Set default animation
    currentAnim = &idleAnim;
    sprite.setTexture(currentAnim->getCurrentTexture(), false);
}
