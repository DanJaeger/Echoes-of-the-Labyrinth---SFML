#include "Game.h"
#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Echoes of the Labyrinth", sf::Style::Fullscreen),
    player()
{
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);

    ResourceManager::getInstance().setTextureBasePath("assets/textures/");
    ResourceManager::getInstance().setFontBasePath("assets/fonts/");

    labyrinth = Labyrinth();

    initLabyrinth();

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
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Game::update(float deltaTime) {
    std::cout << "Elapsed time since previous frame (seconds): "
        << deltaTime << std::endl;

    player.update(deltaTime);

    labyrinth.handleCollisions(player);
    labyrinth.updateTimer();
}

void Game::render() {
    window.clear();

    labyrinth.draw(window);
    player.draw(window);

    window.display();
}

void Game::initLabyrinth()
{
    // Fixed size of each cell
    const int cellPixelSize = 32;

    // Calculate number of rows and columns depending on the screen res
    size_t cols = window.getSize().x / cellPixelSize;
    size_t rows = window.getSize().y / cellPixelSize;

    // Real size of the cells (fixed in case of extra room)
    sf::Vector2f cellSize(
        static_cast<float>(window.getSize().x) / cols,
        static_cast<float>(window.getSize().y) / rows
    );

    labyrinth.generateMazeDFS(rows, cols, cellSize);
}
