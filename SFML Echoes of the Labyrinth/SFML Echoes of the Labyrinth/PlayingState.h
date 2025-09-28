#pragma once
#include "IGameState.h"

/**
 * @brief Main game state where gameplay occurs.
 * Updates and renders the player, labyrinth, HUD, and handles pause input.
 */
class PlayingState : public IGameState {
public:
    /// Handles input (Escape key to pause)
    void handleEvent(Game& game, const sf::Event& ev) override;

    /// Updates player, labyrinth, HUD, and audio
    void update(Game& game, float dt) override;

    /// Draws labyrinth, player, and HUD
    void draw(Game& game, sf::RenderWindow& window) override;
};
