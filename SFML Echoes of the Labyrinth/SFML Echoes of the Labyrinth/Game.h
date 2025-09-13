#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Labyrinth.h"
#include "Player.h"
#include "Walls.h"
#include "GameTimer.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Event event;
    Labyrinth labyrinth;
    Player player;
    GameTimer timer;

    void processEvents();
    void update(float deltaTime);
    void render();

    void initLabyrinth();
    void initTimer();

    void setBasePaths();
    void initWindow();
};

#endif


