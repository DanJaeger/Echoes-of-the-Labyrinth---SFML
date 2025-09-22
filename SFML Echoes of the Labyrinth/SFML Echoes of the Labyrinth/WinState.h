#pragma once
#include "IGameState.h"
#include "MenuScreen.h"
#include <memory>

class WinState : public IGameState {
public:
    WinState(Game& game);

    void handleEvent(Game& game, const sf::Event& ev) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    std::unique_ptr<MenuScreen> menu;
};
