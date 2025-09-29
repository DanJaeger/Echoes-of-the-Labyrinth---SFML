#include "PlayerInput.h"
#include "Config.h"
#include <cmath>

sf::Vector2f PlayerInput::getInputDirection() const {
    sf::Vector2f dir(0.f, 0.f);

    // WASD input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1.f;

    // Arrow keys input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir.x += 1.f;

    // Normalize diagonal movement (so diagonal isn't faster)
    if (dir.x != 0.f && dir.y != 0.f) {
        dir /= Config::Player::DIAGONAL_NORMALIZER;
    }

    return dir;
}
