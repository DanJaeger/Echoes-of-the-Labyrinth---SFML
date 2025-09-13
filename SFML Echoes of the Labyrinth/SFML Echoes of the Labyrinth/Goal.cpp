#include "Goal.h"
#include <iostream>

Goal::Goal(sf::Vector2f size, sf::Vector2f position,
    const sf::Texture& closedTex, const sf::Texture& openTex)
    : body(), collider(&body),
    closedTexture(&closedTex), openTexture(&openTex), openState(false)
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);
    body.setTexture(closedTexture);
}

Goal::Goal(Goal&& other) noexcept
    : body(std::move(other.body)), collider(&body),
    closedTexture(other.closedTexture),
    openTexture(other.openTexture),
    openState(other.openState) {
}

Goal& Goal::operator=(Goal&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);
        closedTexture = other.closedTexture;
        openTexture = other.openTexture;
        openState = other.openState;
    }
    return *this;
}

void Goal::draw(sf::RenderWindow& window) {
    window.draw(body);
}

Collider& Goal::getCollider() {
    return collider;
}

void Goal::open() {
    openState = true;
    body.setTexture(openTexture);
}

bool Goal::isOpen() const {
    return openState;
}

bool Goal::playerReached(const Collider& playerCollider) const {
    return openState && collider.intersects(playerCollider);
}

