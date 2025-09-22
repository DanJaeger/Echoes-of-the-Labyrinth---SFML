#pragma once
#include "IGameState.h"

class PlayingState : public IGameState {
public:
    void handleEvent(Game& game, const sf::Event& ev) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;
};
