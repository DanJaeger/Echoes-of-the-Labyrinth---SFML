#include "Player.h"
#include <cmath>
//COMMENT: CHANGE TO SPRITE ON ALL THE FUNCTIONS WHEN USING A TEXTURE
// Constructor
Player::Player() : collider(shape){
    //sprite.setTexture(ResourceManager::getInstance().getTexture("player.jpeg"));
    //sprite.setPosition(100.f, 100.f);
    shape.setSize(sf::Vector2f(25.0f, 25.0f));   // rectángulo de 50x50 px
    shape.setFillColor(sf::Color::Red);       // color de relleno
    shape.setPosition(100.f, 100.f);
    shape.setOrigin(shape.getSize() / 2.0f);
    speed = 200.f; // default speed
}

void Player::update(float dt) {
    //sprite.move(velocity * speed * dt);
    velocity = input.getInputDirection();
    shape.move(velocity * speed * dt);
}

void Player::draw(sf::RenderWindow& window) {
    //window.draw(sprite);
    window.draw(shape);
}

Collider& Player::getCollider() {
    return collider;
}

// Getters / Setters
sf::Vector2f Player::getPosition() const {
    //return sprite.getPosition();
    return shape.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) {
    //sprite.setPosition(pos);
    shape.setPosition(pos);
}

