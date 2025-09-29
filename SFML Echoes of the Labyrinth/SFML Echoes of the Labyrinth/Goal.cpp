#include "Goal.h"
#include "ResourceManager.h"
#include "Config.h"

// Constructor
Goal::Goal(sf::Vector2f size, sf::Vector2f position,
    const sf::Texture& closedTex, const sf::Texture& openTex)
    : body(),
    collider(&body),
    closedTexture(&closedTex),
    openTexture(&openTex),
    openAnim(Config::Goal::ANIM_FRAME_TIME, false),
    state(GoalState::Closed),
    openState(false)
{
    // Configure size, origin, and position
    body.setSize(size);
    body.setOrigin(size / 2.f);
    body.setPosition(position);

    // Define animation frames (loading from resource paths in Config)
    openAnim.addFrame(Config::Goal::FRAME_1);
    openAnim.addFrame(Config::Goal::FRAME_2);
    openAnim.addFrame(Config::Goal::FRAME_3);

    // Start with the closed texture
    body.setTexture(closedTexture);
}

// Move constructor
Goal::Goal(Goal&& other) noexcept
    : body(std::move(other.body)),
    collider(&body),
    closedTexture(other.closedTexture),
    openTexture(other.openTexture),
    openAnim(std::move(other.openAnim)),
    state(other.state),
    openState(other.openState) {
}

// Move assignment operator
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

// Update goal state (handle animation and transitions)
void Goal::update(float dt) {
    if (state == GoalState::Opening) {
        openAnim.update(dt);

        if (!openAnim.isFinished()) {
            // Use the current frame texture during the animation
            body.setTexture(&openAnim.getCurrentTexture());
        }
        else {
            // Once animation is finished, use the fully open texture
            body.setTexture(openTexture);
            state = GoalState::Opened;
        }
    }
}

// Render the goal
void Goal::draw(sf::RenderWindow& window) {
    window.draw(body);
}

// Access collider
Collider& Goal::getCollider() {
    return collider;
}

// Start opening animation
void Goal::open() {
    if (state == GoalState::Closed) {
        state = GoalState::Opening;
        openAnim.reset();
        body.setTexture(&openAnim.getCurrentTexture());
    }
}

// Check if goal is opening or opened
bool Goal::isOpen() const {
    return state == GoalState::Opening || state == GoalState::Opened;
}

// Check if goal is fully opened
bool Goal::isFullyOpen() const {
    return state == GoalState::Opened;
}

// Check if player has reached the goal
bool Goal::playerReached(const Collider& playerCollider) const {
    return isFullyOpen() && collider.overlaps(playerCollider);
}
