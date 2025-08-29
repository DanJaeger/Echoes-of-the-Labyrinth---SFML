#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

class PlayerInput {
public:
    sf::Vector2f getInputDirection() const;
};

