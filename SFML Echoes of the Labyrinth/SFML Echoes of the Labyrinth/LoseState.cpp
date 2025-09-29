#include "LoseState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Config.h"

LoseState::LoseState(Game& game) {
    // Load font from ResourceManager
    sf::Font& font = ResourceManager::getInstance().getFont(Config::Menu::FONT);

    // Create a menu screen with "Lose" mode enabled
    menu = std::make_unique<MenuScreen>(game.window, font, true);

    // Set menu title and options (from Config constants)
    menu->setTitle(Config::Menu::TEXT_LOSE_TITLE);
    menu->setOptions({ Config::Menu::TEXT_OPTION_RESTART, Config::Menu::TEXT_OPTION_QUIT });
}

void LoseState::handleEvent(Game& game, const sf::Event& ev) {
    // Forward all events to the menu
    menu->processEvent(ev);
}

void LoseState::update(Game& game, float dt) {
    // Check if an option was selected from the menu
    int opt = menu->pollSelectedOption();

    if (opt == Config::Menu::OPTION_RESTART) {
        // Restart the game
        game.labyrinth.reset(game.window.getSize());
        game.player.setPosition(game.labyrinth.getSpawnPoint());
        game.hud.startTimer(sf::seconds(Config::Gameplay::TIME_LIMIT_SECONDS));
        game.changeState(Game::StateType::Playing);
    }
    else if (opt == Config::Menu::OPTION_QUIT) {
        // Quit the game
        game.window.close();
    }
}

void LoseState::draw(Game& game, sf::RenderWindow& window) {
    // Draw game world (background scene)
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);

    // Draw overlay menu
    menu->draw();
}
