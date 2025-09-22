#include "PlayingState.h"
#include "Game.h"
#include "AudioManager.h"

void PlayingState::handleEvent(Game& game, const sf::Event& ev) {
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
        game.changeState(Game::StateType::Paused);
    }
}

void PlayingState::update(Game& game, float dt) {
    game.player.update(dt);
    game.labyrinth.update(dt, game.player);
    game.hud.update(game.labyrinth.getCollectedCount());

    AudioManager::getInstance().update();
}

void PlayingState::draw(Game& game, sf::RenderWindow& window) {
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);
}
