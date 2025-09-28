#pragma once
#include "IGameState.h"
#include "MenuScreen.h"
#include <memory>

/**
 * @brief Game state shown when the player wins.
 * Displays a victory menu with restart and quit options.
 */
class WinState : public IGameState {
public:
    explicit WinState(Game& game);

    /// Handles input (delegated to the menu)
    void handleEvent(Game& game, const sf::Event& ev) override;

    /// Processes menu option selection (restart or quit)
    void update(Game& game, float dt) override;

    /// Draws the game world and overlays the win menu
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    std::unique_ptr<MenuScreen> menu; ///< Victory menu UI
};
