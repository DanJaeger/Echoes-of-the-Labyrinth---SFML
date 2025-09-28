#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IGameState.h"
#include "Labyrinth.h"
#include "Player.h"
#include "HUD.h"
#include "Config.h"

/**
 * @brief Main Game class.
 *
 * This class manages the game loop, window, states (Menu, Playing, etc.),
 * and initializes core systems like audio, labyrinth, and HUD.
 */
class Game {
public:
    Game();

    /// Starts the main game loop
    void run();

    /// All possible states of the game
    enum class StateType { Menu, Playing, Paused, Win, Lose };

    /// Changes the current game state
    void changeState(StateType newState);

    // Core SFML objects
    sf::RenderWindow window;
    sf::Event event;

    // Core gameplay elements
    Player player;
    Labyrinth labyrinth;
    HUD hud;

private:
    /// Pointer to the current active game state (Menu, Playing, etc.)
    std::unique_ptr<IGameState> currentState;

    /// Handles input events from SFML
    void processEvents();

    /// Updates game logic with delta time
    void update(float deltaTime);

    /// Renders all visible objects to the screen
    void render();

    /// Initializes the labyrinth and configures its callbacks
    void initLabyrinth();

    /// Initializes the HUD and configures its callbacks
    void initHUD();

    /// Sets base resource paths for textures and fonts
    void setBasePaths();

    /// Configures SFML window and view
    void initWindow();

    /// Initializes and plays audio
    void initAudio();
};

#endif
