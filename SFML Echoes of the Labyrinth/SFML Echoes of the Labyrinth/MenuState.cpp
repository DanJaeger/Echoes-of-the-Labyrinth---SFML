#include "MenuState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Config.h"

MenuState::MenuState(Game& game) {
    // Load font and initialize menu
    sf::Font& font = ResourceManager::getInstance().getFont(Config::Menu::FONT);
    menu = std::make_unique<MenuScreen>(game.window, font, false);

    // Set menu title and options from Config
    menu->setTitle(Config::Menu::TITLE);
    menu->setOptions({ Config::Menu::TEXT_OPTION_START, Config::Menu::TEXT_OPTION_QUIT });
}

/**
 * @brief Handle input events and pass them to the menu.
 */
void MenuState::handleEvent(Game& game, const sf::Event& ev) {
    menu->processEvent(ev);
}

/**
 * @brief Update menu logic (detect option selection).
 */
void MenuState::update(Game& game, float dt) {
    int opt = menu->pollSelectedOption();
    if (opt == 0) { // Start
        game.changeState(Game::StateType::Playing);
    }
    else if (opt == 1) { // Quit
        game.window.close();
    }
}

/**
 * @brief Render the menu.
 */
void MenuState::draw(Game& game, sf::RenderWindow& window) {
    menu->draw();
}
