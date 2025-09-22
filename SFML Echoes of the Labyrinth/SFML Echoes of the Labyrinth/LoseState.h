#pragma once
#include "IGameState.h"
#include "MenuScreen.h"
#include <memory>

class LoseState : public IGameState {
public:
    LoseState(Game& game);

    void handleEvent(Game& game, const sf::Event& ev) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    std::unique_ptr<MenuScreen> menu;
};
