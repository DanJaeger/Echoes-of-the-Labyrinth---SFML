#include "Player.h"
#include <cmath>
#include "GameTimer.h"

Player::Player() : hitbox(), collider(&hitbox), idleAnim(0.15f), walkAnim(0.1f), faceRight(true), baseScale(1.5f, 1.5f) {
    initHitbox();

    initSprite();
    
    initAnimation();

    speed = 200.f; // default speed
}

void Player::update(float dt) {
    velocity = input.getInputDirection();
    hitbox.move(velocity * speed * dt);

    updateAnimation(velocity, dt);

    moveSpriteWithHitbox();
    
}

void Player::updateAnimation(sf::Vector2f velocity, float dt)
{
    if (velocity.x != 0.f || velocity.y != 0.f) {
        if (currentAnim != &walkAnim) {
            currentAnim = &walkAnim;
            currentAnim->reset();
        }
        if (velocity.x < 0.f) faceRight = false;
        else if (velocity.x > 0.f) faceRight = true;
    }
    else {
        if (currentAnim != &idleAnim) {
            currentAnim = &idleAnim;
            currentAnim->reset();
        }
    }

    currentAnim->update(dt);
    sprite.setTexture(currentAnim->getCurrentTexture(), false);

    if (faceRight) {
        sprite.setScale(baseScale.x, baseScale.y);
    }
    else {
        sprite.setScale(-baseScale.x, baseScale.y);
    }
}

void Player::moveSpriteWithHitbox()
{
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.f,
        sprite.getLocalBounds().height / 1.5f
    );

    sprite.setPosition(hitbox.getPosition());
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    //window.draw(shape); // For debugging
}

Collider& Player::getCollider() {
    return collider;
}

// Getters / Setters
sf::Vector2f Player::getPosition() const {
    return hitbox.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) {
    hitbox.setPosition(pos);
    sprite.setPosition(pos);
}

void Player::initHitbox() {
    hitbox.setSize(sf::Vector2f(25.0f, 25.0f));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);      // For debugging
    hitbox.setOutlineThickness(1.f);
    hitbox.setOrigin(hitbox.getSize() / 2.0f);
    hitbox.setPosition({ 100.f, 100.f });
}

void Player::initSprite()
{
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.f,
        sprite.getLocalBounds().height / 1.5f
    );
    sprite.setPosition(hitbox.getPosition());
    sprite.setScale(baseScale);
}

void Player::initAnimation()
{
    idleAnim.addFrame("player/idle_0.png");
    idleAnim.addFrame("player/idle_1.png");
    idleAnim.addFrame("player/idle_2.png");
    idleAnim.addFrame("player/idle_3.png");

    walkAnim.addFrame("player/run_0.png");
    walkAnim.addFrame("player/run_1.png");
    walkAnim.addFrame("player/run_2.png");
    walkAnim.addFrame("player/run_3.png");

    currentAnim = &idleAnim;
    sprite.setTexture(currentAnim->getCurrentTexture(), false);
}