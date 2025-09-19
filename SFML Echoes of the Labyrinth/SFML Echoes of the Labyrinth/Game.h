#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Labyrinth.h"
#include "Player.h"
#include "Walls.h"
#include "HUD.h"

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

    void processEvents();
    void update(float deltaTime);
    void render();

    void initLabyrinth();
    void initHUD();

    void setBasePaths();
    void initWindow();
};

#endif


