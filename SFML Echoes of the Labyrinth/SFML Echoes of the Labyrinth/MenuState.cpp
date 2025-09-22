#include "MenuState.h"
#include "Game.h"
#include "ResourceManager.h"

MenuState::MenuState(Game& game) {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    menu = std::make_unique<MenuScreen>(game.window, font, false);
    menu->setTitle("Echoes of the Labyrinth");
    menu->setOptions({ "Start", "Quit" });
}

void MenuState::handleEvent(Game& game, const sf::Event& ev) {
    menu->processEvent(ev);
}

void MenuState::update(Game& game, float dt) {
    int opt = menu->pollSelectedOption();
    if (opt == 0) { // Start
        game.changeState(Game::StateType::Playing);
    }
    else if (opt == 1) { // Quit
        game.window.close();
    }
}

void MenuState::draw(Game& game, sf::RenderWindow& window) {
    menu->draw();
}
