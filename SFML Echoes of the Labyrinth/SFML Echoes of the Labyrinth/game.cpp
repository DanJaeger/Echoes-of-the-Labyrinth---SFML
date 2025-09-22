#include "Game.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "PausedState.h"
#include "WinState.h"
#include "LoseState.h"

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Echoes of the Labyrinth", sf::Style::Fullscreen),
    player()
{
    initWindow();

    initAudio();

    setBasePaths();

    initLabyrinth();

    initHUD();

    changeState(StateType::Menu);
}

void Game::changeState(StateType newState) {
    switch (newState) {
    case StateType::Menu:   currentState = std::make_unique<MenuState>(*this); break;
    case StateType::Playing:currentState = std::make_unique<PlayingState>(); break;
    case StateType::Paused: currentState = std::make_unique<PausedState>(*this); break;
    case StateType::Win:    currentState = std::make_unique<WinState>(*this); break;
    case StateType::Lose:   currentState = std::make_unique<LoseState>(*this); break;
    }
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
        if (currentState) currentState->handleEvent(*this, event);
    }
}

void Game::update(float deltaTime) {
    static float elapsedDebug = 0.f;
    elapsedDebug += deltaTime;
    if (elapsedDebug >= 1.f) {
        std::cout << "FPS: " << 1.f / deltaTime << std::endl;
        elapsedDebug = 0.f;
    }
    if (currentState) currentState->update(*this, deltaTime);
}

void Game::render() {
    window.clear();

    if (currentState) currentState->draw(*this, window);

    window.display();
}

void Game::initLabyrinth()
{
    labyrinth = Labyrinth();
    labyrinth.generate(window.getSize());

    labyrinth.setOnWin([this]() {
        changeState(StateType::Win);
        });
}

void Game::initHUD() {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    hud.setFont(font);
    hud.setTimerPosition({ 0.f, 0.f });       
    hud.setTimerStyle(24, sf::Color::White, sf::Color::Black, 2.f);
    hud.setMargin({ 15.f, 15.f });

    hud.setOnTimeout([this]() {
        changeState(StateType::Lose);
        });

    hud.startTimer(sf::seconds(240));

    hud.setCollectablesIcon(ResourceManager::getInstance().getTexture("items/collectable.png"));
    hud.setCollectablesTotal(labyrinth.getCollectablesCount());
    hud.setCollectablesPosition({ 0.f, 30.f });       
    hud.setCollectablesSpacing(10.f);
}