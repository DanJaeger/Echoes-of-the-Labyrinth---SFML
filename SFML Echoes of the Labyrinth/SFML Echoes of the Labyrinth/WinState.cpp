#include "WinState.h"
#include "Game.h"
#include "ResourceManager.h"

WinState::WinState(Game& game) {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    menu = std::make_unique<MenuScreen>(game.window, font, true);
    menu->setTitle("You Won!");
    menu->setOptions({ "Restart", "Quit" });
}

void WinState::handleEvent(Game& game, const sf::Event& ev) {
    menu->processEvent(ev);
}

void WinState::update(Game& game, float dt) {
    int opt = menu->pollSelectedOption();
    if (opt == 0) { // Restart
        game.labyrinth.reset(game.window.getSize());
        game.player.setPosition(game.labyrinth.getSpawnPoint());
        game.hud.startTimer(sf::seconds(240));
        game.changeState(Game::StateType::Playing);
    }
    else if (opt == 1) { // Quit
        game.window.close();
    }
}

void WinState::draw(Game& game, sf::RenderWindow& window) {
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);
    menu->draw();
}
