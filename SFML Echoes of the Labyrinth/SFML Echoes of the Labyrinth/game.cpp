#include "Game.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include <iostream>
#include <filesystem>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Echoes of the Labyrinth", sf::Style::Fullscreen),
    player()
{
    initWindow();

    initAudio();

    setBasePaths();

    initLabyrinth();

    initHUD();

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

void Game::initAudio() {
    auto& audio = AudioManager::getInstance();

    //SFX
    audio.loadSound("pickup", "assets/audio/pickup.wav");
    audio.loadSound("openChest", "assets/audio/open_chest.wav");

    audio.playMusic("assets/audio/bg_music.ogg", true, 50.f);
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

        if (state == GameState::Menu && mainMenu) {
            mainMenu->processEvent(event);
        }
        else if (state == GameState::Paused && pauseMenu) {
            pauseMenu->processEvent(event);
        }
        else if (state == GameState::Win && winMenu) {
            winMenu->processEvent(event);
        }
        else if (state == GameState::Lose && loseMenu) {
            loseMenu->processEvent(event);
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
        {
            if (state == GameState::Playing) {
                state = GameState::Paused;
                pauseMenu->reset();
            }
            else if (state == GameState::Paused) {
                state = GameState::Playing;
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

    if (state == GameState::Menu) {
        int opt = mainMenu->pollSelectedOption();
        if (opt == 0) { // Start
            state = GameState::Playing;
            mainMenu->reset();
        }
        else if (opt == 1) { // Quit
            window.close();
        }
    }
    else if (state == GameState::Paused) {
        int opt = pauseMenu->pollSelectedOption();
        if (opt == 0) { // Restart
            labyrinth.reset(window.getSize());
            player.setPosition(labyrinth.getSpawnPoint());
            hud.startTimer(sf::seconds(240));
            state = GameState::Playing;
            pauseMenu->reset();
        }
        else if (opt == 1) { // Quit
            window.close();
        }
    }
    else if (state == GameState::Win) {
        int opt = winMenu->pollSelectedOption();
        if (opt == 0) { // Restart
            labyrinth.reset(window.getSize());
            player.setPosition(labyrinth.getSpawnPoint());
            hud.startTimer(sf::seconds(240));
            state = GameState::Playing;
            winMenu->reset();
        }
        else if (opt == 1) { // Quit
            window.close();
        }
    }
    else if (state == GameState::Lose) {
        int opt = loseMenu->pollSelectedOption();
        if (opt == 0) { // Restart
            labyrinth.reset(window.getSize());
            player.setPosition(labyrinth.getSpawnPoint());
            hud.startTimer(sf::seconds(240));
            state = GameState::Playing;
            loseMenu->reset();
        }
        else if (opt == 1) { // Quit
            window.close();
        }
    }
    else if (state == GameState::Playing) {
        player.update(deltaTime);
        labyrinth.update(deltaTime, player);
        hud.update(labyrinth.getCollectedCount());

        AudioManager::getInstance().update();
    }
}

void Game::render() {
    window.clear();

    if (state == GameState::Menu) {
        mainMenu->draw();
    }
    else if (state == GameState::Paused) {
        labyrinth.draw(window);
        player.draw(window);
        hud.draw(window);
        pauseMenu->draw();
    }
    else if (state == GameState::Playing) {
        labyrinth.draw(window);
        player.draw(window);
        hud.draw(window);
    }
    else if (state == GameState::Win) {
        labyrinth.draw(window);
        player.draw(window);
        hud.draw(window);
        winMenu->draw();
    }
    else if (state == GameState::Lose) {
        labyrinth.draw(window);
        player.draw(window);
        hud.draw(window);
        loseMenu->draw();
    }

    window.display();
}

void Game::initLabyrinth()
{
    labyrinth = Labyrinth();
    labyrinth.generate(window.getSize());

    labyrinth.setOnWin([this]() {
        state = GameState::Win;
        });
}

void Game::initHUD() {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    hud.setFont(font);
    hud.setTimerPosition({ 0.f, 0.f });       
    hud.setTimerStyle(24, sf::Color::White, sf::Color::Black, 2.f);
    hud.setMargin({ 15.f, 15.f });

    hud.setOnTimeout([this]() {
        state = GameState::Lose;
        });

    hud.startTimer(sf::seconds(240));

    hud.setCollectablesIcon(ResourceManager::getInstance().getTexture("items/collectable.png"));
    hud.setCollectablesTotal(labyrinth.getCollectablesCount());
    hud.setCollectablesPosition({ 0.f, 30.f });       
    hud.setCollectablesSpacing(10.f);

    mainMenu = std::make_unique<MenuScreen>(window, font, false);
    mainMenu->setTitle("Echoes of the Labyrinth");
    mainMenu->setOptions({ "Start", "Quit" });

    pauseMenu = std::make_unique<MenuScreen>(window, font, true);
    pauseMenu->setTitle("Pause");
    pauseMenu->setOptions({ "Restart", "Quit" });

    winMenu = std::make_unique<MenuScreen>(window, font, true);
    winMenu->setTitle("¡You Won!");
    winMenu->setOptions({ "Restart", "Quit" });

    loseMenu = std::make_unique<MenuScreen>(window, font, true);
    loseMenu->setTitle("You Lost");
    loseMenu->setOptions({ "Restart", "Quit" });
}