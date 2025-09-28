#pragma once
#include "IGameState.h"
#include "MenuScreen.h"
#include <memory>

/**
 * @brief Game state when the game is paused.
 * Displays a pause menu that allows resuming, restarting, or quitting.
 */
class PausedState : public IGameState {
public:
    explicit PausedState(Game& game);

    /// Handles pause menu input and Escape key to resume
    void handleEvent(Game& game, const sf::Event& ev) override;

    /// Processes menu selections (restart or quit)
    void update(Game& game, float dt) override;

    /// Draws the game world and overlays the pause menu
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    std::unique_ptr<MenuScreen> menu; ///< Pause menu UI
};
