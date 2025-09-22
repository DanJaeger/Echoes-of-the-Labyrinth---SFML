#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Labyrinth.h"
#include "Player.h"
#include "Walls.h"
#include "HUD.h"
#include "MenuScreen.h"

enum class GameState {
    Menu,
    Playing,
    Paused,
    Win, 
    Lose
};

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Event event;
    Labyrinth labyrinth;
    Player player;
    HUD hud;

    GameState state;
    std::unique_ptr<MenuScreen> mainMenu;
    std::unique_ptr<MenuScreen> pauseMenu;
    std::unique_ptr<MenuScreen> winMenu;
    std::unique_ptr<MenuScreen> loseMenu;

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


