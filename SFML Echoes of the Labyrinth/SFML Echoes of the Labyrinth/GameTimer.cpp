#include "GameTimer.h"
#include <iostream>
#include <algorithm>

// Constructor: set default text properties and initial position
GameTimer::GameTimer() {
    text.setCharacterSize(Config::HUD::FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(Config::HUD::OUTLINE_THICKNESS);

    basePosition = Config::HUD::TIMER_POSITION;
    margin = Config::HUD::MARGIN;
    updatePosition();
}

// Set absolute position of the timer
void GameTimer::setPosition(const sf::Vector2f& pos) {
    basePosition = pos;
    updatePosition();
}

// Set margin offset from base position
void GameTimer::setMargin(const sf::Vector2f& m) {
    margin = m;
    updatePosition();
}

// Recalculate the text position
void GameTimer::updatePosition() {
    text.setPosition(basePosition + margin);
}

// Start the timer with a given limit
void GameTimer::start(sf::Time limit) {
    timeLimit = limit;
    clock.restart();
    running = true;
}

// Reset timer and start counting again
void GameTimer::reset() {
    clock.restart();
    running = true;
}

// Update remaining time and check timeout
void GameTimer::update() {
    if (!running) return;

    sf::Time elapsed = clock.getElapsedTime();
    sf::Time remaining = timeLimit - elapsed;

    // Clamp remaining seconds to 0
    int seconds = std::max(0, (int)remaining.asSeconds());
    text.setString("Time: " + std::to_string(seconds));

    // If time is up, stop and trigger callback
    if (remaining.asSeconds() <= 0) {
        running = false;
        if (onTimeout) {
            onTimeout();
        }
    }
}

// Render the timer text
void GameTimer::draw(sf::RenderWindow& window) {
    window.draw(text);
}

// Configure font for the timer text
void GameTimer::setFont(const sf::Font& font) {
    text.setFont(font);
}

// Change font size
void GameTimer::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

// Set fill color, outline color, and thickness
void GameTimer::setColors(sf::Color fill, sf::Color outline, float thickness) {
    text.setFillColor(fill);
    text.setOutlineColor(outline);
    text.setOutlineThickness(thickness);
}

// Assign callback for when timer runs out
void GameTimer::setOnTimeout(std::function<void()> callback) {
    onTimeout = callback;
}
