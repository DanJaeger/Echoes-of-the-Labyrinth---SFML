#include "Goal.h"
#include "ResourceManager.h"
#include <iostream>

Goal::Goal(sf::Vector2f size, sf::Vector2f position,
    const sf::Texture& closedTex, const sf::Texture& openTex)
    : body(), collider(&body),
    closedTexture(&closedTex),
    openTexture(&openTex),
    openAnim(0.2f, false),
    state(GoalState::Closed),
    openState(false)
{
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    openAnim.addFrame("items/chest_empty_0.png");
    openAnim.addFrame("items/chest_empty_1.png");
    openAnim.addFrame("items/chest_full_open.png");

    body.setTexture(closedTexture);
}

Goal::Goal(Goal&& other) noexcept
    : body(std::move(other.body)), collider(&body),
    closedTexture(other.closedTexture),
    openTexture(other.openTexture),
    openAnim(std::move(other.openAnim)),
    state(other.state),
    openState(other.openState) {
}

Goal& Goal::operator=(Goal&& other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        collider.rebind(&body);
        closedTexture = other.closedTexture;
        openTexture = other.openTexture;
        openAnim = std::move(other.openAnim);
        state = other.state;
        openState = other.openState;
    }
    return *this;
}

void Goal::update(float dt) {
    if (state == GoalState::Opening) {
        openAnim.update(dt);

        if (!openAnim.isFinished()) {
            body.setTexture(&openAnim.getCurrentTexture());
        }
        else {
            body.setTexture(openTexture);
            state = GoalState::Opened;
        }
    }
}

void Goal::draw(sf::RenderWindow& window) {
    window.draw(body);
}

Collider& Goal::getCollider() {
    return collider;
}

void Goal::open() {
    if (state == GoalState::Closed) {
        state = GoalState::Opening;
        openAnim.reset();
        body.setTexture(&openAnim.getCurrentTexture());
    }
}

bool Goal::isOpen() const {
    return state == GoalState::Opening || state == GoalState::Opened;
}

bool Goal::isFullyOpen() const
{
    return state == GoalState::Opened;
}

bool Goal::playerReached(const Collider& playerCollider) const {
    return isFullyOpen() && collider.intersects(playerCollider);
}

