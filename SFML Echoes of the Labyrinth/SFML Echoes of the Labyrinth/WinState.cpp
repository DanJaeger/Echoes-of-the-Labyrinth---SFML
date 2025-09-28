#include "WinState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Config.h"

WinState::WinState(Game& game) {
    // Load font
    sf::Font& font = ResourceManager::getInstance().getFont(Config::Menu::FONT);

    // Create win menu
    menu = std::make_unique<MenuScreen>(game.window, font, true);

    // Configure menu title and options
    menu->setTitle(Config::Menu::TEXT_WIN_TITLE);
    menu->setOptions({ Config::Menu::TEXT_OPTION_RESTART, Config::Menu::TEXT_OPTION_QUIT });
}

void WinState::handleEvent(Game& game, const sf::Event& ev) {
    menu->processEvent(ev);
}

void WinState::update(Game& game, float dt) {
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

void WinState::draw(Game& game, sf::RenderWindow& window) {
    // Draw game scene behind win menu
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);

    // Overlay win menu
    menu->draw();
}
