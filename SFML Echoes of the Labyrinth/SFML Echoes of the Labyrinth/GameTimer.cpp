#include "GameTimer.h"
#include <iostream>
#include <algorithm>

GameTimer::GameTimer() {
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2.f);

    basePosition = { 10.f, 10.f };
    margin = { 0.f, 0.f };
    updatePosition();
}

void GameTimer::setPosition(const sf::Vector2f& pos) {
    basePosition = pos;
    updatePosition();
}

void GameTimer::setMargin(const sf::Vector2f& m) {
    margin = m;
    updatePosition();
}

void GameTimer::updatePosition() {
    text.setPosition(basePosition + margin);
}

void GameTimer::start(sf::Time limit) {
    timeLimit = limit;
    clock.restart();
    running = true;
}

void GameTimer::reset() {
    clock.restart();
    running = true;
}

void GameTimer::update() {
    if (!running) return;

    sf::Time elapsed = clock.getElapsedTime();
    sf::Time remaining = timeLimit - elapsed;

    int seconds = std::max(0, (int)remaining.asSeconds());
    text.setString("Tiempo: " + std::to_string(seconds));

    if (remaining.asSeconds() <= 0) {
        running = false;
        if (onTimeout) {
            onTimeout();
        }
    }
}

void GameTimer::draw(sf::RenderWindow& window) {
    window.draw(text);
}

void GameTimer::setFont(const sf::Font& font) {
    text.setFont(font);
}

void GameTimer::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void GameTimer::setColors(sf::Color fill, sf::Color outline, float thickness) {
    text.setFillColor(fill);
    text.setOutlineColor(outline);
    text.setOutlineThickness(thickness);
}

void GameTimer::setOnTimeout(std::function<void()> callback) {
    onTimeout = callback;
}


