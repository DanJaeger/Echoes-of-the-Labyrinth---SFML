#pragma once
#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "Config.h"

/**
 * @brief A countdown game timer with visual representation.
 *
 * Displays remaining time on the screen, can be configured
 * with font, colors, margins, and executes a callback when time runs out.
 */
class GameTimer {
public:
    GameTimer();

    /// Start the timer with a time limit
    void start(sf::Time limit);

    /// Reset and restart the timer
    void reset();

    /// Update timer logic (check elapsed time, trigger timeout if needed)
    void update();

    /// Draw the timer text to the given window
    void draw(sf::RenderWindow& window);

    /// Set the font used for the timer text
    void setFont(const sf::Font& font);

    /// Set base position of the timer
    void setPosition(const sf::Vector2f& pos);

    /// Set text size
    void setCharacterSize(unsigned int size);

    /// Configure text colors and outline
    void setColors(sf::Color fill, sf::Color outline = sf::Color::Black, float thickness = 2.f);

    /// Set margin offset from base position
    void setMargin(const sf::Vector2f& margin);

    /// Assign a callback to be triggered when time runs out
    void setOnTimeout(std::function<void()> callback);

private:
    // Core timer logic
    sf::Clock clock;
    sf::Time timeLimit;
    bool running = false;

    // Text for displaying countdown
    sf::Text text;

    // Position control
    sf::Vector2f basePosition;
    sf::Vector2f margin;

    // Callback when timer reaches zero
    std::function<void()> onTimeout;

    /// Updates the text position based on base position and margin
    void updatePosition();
};

#endif
