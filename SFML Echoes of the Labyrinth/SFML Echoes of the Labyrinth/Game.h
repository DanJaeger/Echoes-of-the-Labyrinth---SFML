#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IGameState.h" 
#include "Labyrinth.h"
#include "Player.h"
#include "HUD.h"

class IGameState;

class Game {
public:
    Game();
    void run();

    enum class StateType { Menu, Playing, Paused, Win, Lose };

    void changeState(StateType newState);

    sf::RenderWindow window;
    sf::Event event;
    Player player;
    Labyrinth labyrinth;
    HUD hud;

private:
    std::unique_ptr<IGameState> currentState;

    void processEvents();
    void update(float deltaTime);
    void render();

    void initLabyrinth();
    void initHUD();

    void setBasePaths();
    void initWindow();

    void initAudio();
};

#endif


