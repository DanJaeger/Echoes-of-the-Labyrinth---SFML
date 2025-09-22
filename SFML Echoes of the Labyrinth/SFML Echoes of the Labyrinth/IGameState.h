#pragma once
#include <SFML/Graphics.hpp>

class Game;

class IGameState {
public:
    virtual ~IGameState() = default;

    virtual void handleEvent(Game& game, const sf::Event& ev) = 0;
    virtual void update(Game& game, float dt) = 0;
    virtual void draw(Game& game, sf::RenderWindow& window) = 0;
};
