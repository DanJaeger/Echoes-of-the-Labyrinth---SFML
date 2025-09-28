#pragma once
#include <SFML/Graphics.hpp>

class Game;

/**
 * @brief Interface for all game states.
 *
 * Defines the contract that every game state (Menu, Playing, Paused, etc.)
 * must follow. This ensures that the game state machine can manage states
 * consistently.
 */
class IGameState {
public:
    virtual ~IGameState() = default; ///< Virtual destructor for safe cleanup

    /**
     * @brief Handle input events specific to the current state.
     *
     * @param game Reference to the main Game instance.
     * @param ev The SFML event to be processed.
     */
    virtual void handleEvent(Game& game, const sf::Event& ev) = 0;

    /**
     * @brief Update the logic of the current state.
     *
     * @param game Reference to the main Game instance.
     * @param dt Delta time in seconds since the last update.
     */
    virtual void update(Game& game, float dt) = 0;

    /**
     * @brief Render the current state on the screen.
     *
     * @param game Reference to the main Game instance.
     * @param window The render window where the state will draw its elements.
     */
    virtual void draw(Game& game, sf::RenderWindow& window) = 0;
};
