#include "Game.h"
#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Echoes of the Labyrinth", sf::Style::Fullscreen),
    player()
{
    initWindow();

    setBasePaths();

    initLabyrinth();

    initTimer();

}

void Game::setBasePaths()
{
    ResourceManager::getInstance().setTextureBasePath("assets/textures/");
    ResourceManager::getInstance().setFontBasePath("assets/fonts/");
}

void Game::initWindow()
{
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);
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
    static float elapsedDebug = 0.f;
    elapsedDebug += deltaTime;
    if (elapsedDebug >= 1.f) {
        std::cout << "FPS: " << 1.f / deltaTime << std::endl;
        elapsedDebug = 0.f;
    }

    player.update(deltaTime);

    labyrinth.update(deltaTime, player);

    timer.update();
}

void Game::render() {
    window.clear();

    labyrinth.draw(window);
    player.draw(window);
    timer.draw(window);

    window.display();
}

void Game::initLabyrinth()
{
    labyrinth = Labyrinth();
    labyrinth.generate(window.getSize());

    labyrinth.setOnWin([this]() {
        labyrinth.reset(window.getSize());
        player.setPosition(labyrinth.getSpawnPoint());
        timer.start(sf::seconds(240));
        });
}

void Game::initTimer() {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    timer.setFont(font);
    timer.setCharacterSize(24);
    timer.setColors(sf::Color::White, sf::Color::Black, 2.f);
    timer.setPosition({ 10.f, 10.f });

    timer.setOnTimeout([this]() {
        labyrinth.reset(window.getSize());
        player.setPosition(labyrinth.getSpawnPoint());
        timer.start(sf::seconds(240));
        });

    timer.start(sf::seconds(240));
}