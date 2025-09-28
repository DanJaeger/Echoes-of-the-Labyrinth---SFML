#pragma once
#include "IGameState.h"
#include "MenuScreen.h"
#include <memory>

/**
 * @brief Game state shown when the player loses.
 * Displays a menu that allows restarting the game or quitting.
 */
class LoseState : public IGameState {
public:
    explicit LoseState(Game& game);

    /**
     * @brief Handle input events (delegated to the menu).
     */
    void handleEvent(Game& game, const sf::Event& ev) override;

    /**
     * @brief Update logic for the Lose state.
     * Processes menu option selection.
     */
    void update(Game& game, float dt) override;

    /**
     * @brief Draws the game scene behind the menu (labyrinth, player, HUD)
     * and then overlays the Lose menu.
     */
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    std::unique_ptr<MenuScreen> menu; ///< Menu instance for restart/quit options
};
