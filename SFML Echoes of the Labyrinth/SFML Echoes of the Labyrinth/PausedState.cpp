#include "PausedState.h"
#include "Game.h"
#include "ResourceManager.h"

PausedState::PausedState(Game& game) {
    sf::Font& font = ResourceManager::getInstance().getFont("clock.ttf");
    menu = std::make_unique<MenuScreen>(game.window, font, true);
    menu->setTitle("Pause");
    menu->setOptions({ "Restart", "Quit" });
}

void PausedState::handleEvent(Game& game, const sf::Event& ev) {
    menu->processEvent(ev);

    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
        game.changeState(Game::StateType::Playing);
    }
}

void PausedState::update(Game& game, float dt) {
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

void PausedState::draw(Game& game, sf::RenderWindow& window) {
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);
    menu->draw();
}
