#include "PlayingState.h"
#include "Game.h"
#include "AudioManager.h"
#include "Config.h"

void PlayingState::handleEvent(Game& game, const sf::Event& ev) {
    // If Escape is pressed, switch to Paused state
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
        game.changeState(Game::StateType::Paused);
    }
}

void PlayingState::update(Game& game, float dt) {
    // Update game entities
    game.player.update(dt);
    game.labyrinth.update(dt, game.player);
    game.hud.update(game.labyrinth.getCollectedCount());

    // Update audio manager
    AudioManager::getInstance().update();
}

void PlayingState::draw(Game& game, sf::RenderWindow& window) {
    // Draw gameplay elements
    game.labyrinth.draw(window);
    game.player.draw(window);
    game.hud.draw(window);
}
