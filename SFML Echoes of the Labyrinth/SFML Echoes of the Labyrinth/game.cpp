#include "Game.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "PausedState.h"
#include "WinState.h"
#include "LoseState.h"

// Constructor: sets up window, audio, resources, labyrinth, HUD, and initial state
Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Echoes of the Labyrinth", sf::Style::Fullscreen),
    player()
{
    initWindow();
    initAudio();
    setBasePaths();
    initLabyrinth();
    initHUD();

    // Start the game in Menu state
    changeState(StateType::Menu);
}

// Switch between different game states
void Game::changeState(StateType newState) {
    switch (newState) {
    case StateType::Menu:    currentState = std::make_unique<MenuState>(*this); break;
    case StateType::Playing: currentState = std::make_unique<PlayingState>(); break;
    case StateType::Paused:  currentState = std::make_unique<PausedState>(*this); break;
    case StateType::Win:     currentState = std::make_unique<WinState>(*this); break;
    case StateType::Lose:    currentState = std::make_unique<LoseState>(*this); break;
    }
}

// Set resource base paths for ResourceManager
void Game::setBasePaths() {
    ResourceManager::getInstance().setTextureBasePath("assets/textures/");
    ResourceManager::getInstance().setFontBasePath("assets/fonts/");
}

// Configure window and view
void Game::initWindow() {
    window.setFramerateLimit(Config::Window::FPS);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);
}

// Initialize audio system and play background music
void Game::initAudio() {
    auto& audio = AudioManager::getInstance();

    // Load SFX
    audio.loadSound("pickup", "assets/audio/pickup.wav");
    audio.loadSound("openChest", "assets/audio/open_chest.wav");

    // Play looping background music
    audio.playMusic("assets/audio/bg_music.ogg", true, Config::Audio::MUSIC_VOLUME);
}

// Main game loop
void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();

        // Calculate time since last frame
        float deltaTime = clock.restart().asSeconds();

        update(deltaTime);
        render();
    }
}

// Handle window and input events
void Game::processEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Forward event handling to the current state
        if (currentState) currentState->handleEvent(*this, event);
    }
}

// Update game logic
void Game::update(float deltaTime) {
    // Debug: print FPS every second
    //static float elapsedDebug = 0.f;
    //elapsedDebug += deltaTime;
    //if (elapsedDebug >= 1.f) {
    //    std::cout << "FPS: " << 1.f / deltaTime << std::endl;
    //    elapsedDebug = 0.f;
    //}

    // Update current state
    if (currentState) currentState->update(*this, deltaTime);
}

// Render all visible elements
void Game::render() {
    window.clear();

    if (currentState) currentState->draw(*this, window);

    window.display();
}

// Initialize labyrinth and bind win condition
void Game::initLabyrinth() {
    labyrinth = Labyrinth();
    labyrinth.generate(window.getSize());

    // Change to Win state when player reaches labyrinth exit
    labyrinth.setOnWin([this]() {
        changeState(StateType::Win);
        });
}

// Initialize HUD and bind timeout condition
void Game::initHUD() {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");

    hud.setFont(font);
    hud.setTimerPosition(Config::HUD::TIMER_POSITION);
    hud.setTimerStyle(Config::HUD::FONT_SIZE, sf::Color::White, sf::Color::Black, Config::HUD::OUTLINE_THICKNESS);
    hud.setMargin(Config::HUD::MARGIN);

    // Lose the game if time runs out
    hud.setOnTimeout([this]() {
        changeState(StateType::Lose);
        });

    hud.startTimer(sf::seconds(Config::Gameplay::TIME_LIMIT_SECONDS));

    // Setup collectables HUD
    hud.setCollectablesIcon(ResourceManager::getInstance().getTexture("items/collectable.png"));
    hud.setCollectablesTotal(labyrinth.getCollectablesCount());
    hud.setCollectablesPosition(Config::HUD::COLLECTABLES_POSITION);
    hud.setCollectablesSpacing(Config::HUD::Collectables::SPACING);
}
