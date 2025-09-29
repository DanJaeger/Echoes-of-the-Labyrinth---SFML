#include "PausedState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Config.h"

PausedState::PausedState(Game& game) {
    // Load font
    sf::Font& font = ResourceManager::getInstance().getFont(Config::Menu::FONT);

    // Create pause menu
    menu = std::make_unique<MenuScreen>(game.window, font, true);

    // Configure menu title and options
    menu->setTitle(Config::Menu::TEXT_PAUSE_TITLE);
    menu->setOptions({ Config::Menu::TEXT_OPTION_RESTART, Config::Menu::TEXT_OPTION_QUIT });
}

void PausedState::handleEvent(Game& game, const sf::Event& ev) {
    // Forward all input events to the menu
    menu->processEvent(ev);

    // If Escape is pressed, return to Playing state
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
        game.changeState(Game::StateType::Playing);
    }
}

void PausedState::update(Game& game, float dt) {
    int opt = menu->pollSelectedOption();

    if (opt == Config::Menu::OPTION_RESTART) {
        // Restart game
        game.labyrinth.reset(game.window.getSize());
        game.player.setPosition(game.labyrinth.getSpawnPoint());
        game.hud.startTimer(sf::seconds(Config::Gameplay::TIME_LIMIT_SECONDS));
        game.changeState(Game::StateType::Playing);
    }
    else if (opt == Config::Menu::OPTION_QUIT) {
        // Quit game
        game.window.close();
    }
}

void PausedState::draw(Game& game, sf::RenderWindow& window) {
    // Draw game scene behind pause menu
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);

    // Overlay pause menu
    menu->draw();
}
