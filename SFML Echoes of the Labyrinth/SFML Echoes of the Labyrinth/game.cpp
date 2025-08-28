#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(640, 480), "Echoes of the Labyrinth"),
    labyrinth("maze.jpg", window.getSize())
{
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);

    ResourceManager::getInstance().setBasePath("assets/textures/");
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();

        float deltaTime = clock.restart().asSeconds();

        update(deltaTime);

        render();
    }
}

void Game::processEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    std::cout << "Elapsed time since previous frame (seconds): "
        << deltaTime << std::endl;

    player.handleInput();
    player.update(deltaTime);
}

void Game::render() {
    window.clear();

    labyrinth.draw(window);
    player.draw(window);

    window.display();
}