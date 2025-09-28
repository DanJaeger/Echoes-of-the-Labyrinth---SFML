#pragma once
#include <SFML/Graphics.hpp>
#include "GameTimer.h"
#include "HUDCollectables.h"

/**
 * @brief Manages the in-game Heads-Up Display (HUD).
 *
 * The HUD displays two key elements:
 * - A countdown timer (GameTimer).
 * - The collectables tracker (HUDCollectables).
 *
 * It provides methods to configure and update both components, as well
 * as to render them to the game window.
 */
class HUD {
public:
    HUD() = default;

    /// Set the font used by the timer
    void setFont(sf::Font& font) {
        timer.setFont(font);
    }

    /// Configure the style of the timer text
    void setTimerStyle(unsigned int size, sf::Color fill,
        sf::Color outline, float thickness) {
        timer.setCharacterSize(size);
        timer.setColors(fill, outline, thickness);
    }

    /// Set the position of the timer on screen
    void setTimerPosition(const sf::Vector2f& pos) {
        timer.setPosition(pos);
    }

    /// Assign a callback to be executed when the timer reaches zero
    void setOnTimeout(std::function<void()> callback) {
        timer.setOnTimeout(callback);
    }

    /// Start the countdown timer with a given duration
    void startTimer(sf::Time duration) {
        timer.start(duration);
    }

    /// Apply a margin offset to both timer and collectables
    void setMargin(const sf::Vector2f& margin) {
        timer.setMargin(margin);
        collectables.setMargin(margin);
    }

    /// Set spacing between collectable icons
    void setCollectablesSpacing(float space) {
        collectables.setSpacing(space);
    }

    /// Define the total number of collectables in the level
    void setCollectablesTotal(int total) {
        collectables.setTotal(total);
    }

    /// Update the number of collectables already collected
    void setCollectablesCollected(int collected) {
        collectables.setCollected(collected);
    }

    /// Set the texture/icon used to represent collectables
    void setCollectablesIcon(const sf::Texture& texture) {
        collectables.setIcon(texture);
    }

    /// Define the base position of the collectables UI
    void setCollectablesPosition(const sf::Vector2f& pos) {
        collectables.setPosition(pos);
    }

    /**
     * @brief Update the HUD components.
     * @param collectedCount Number of collectables collected so far.
     */
    void update(int collectedCount) {
        setCollectablesCollected(collectedCount);
        timer.update();
    }

    /// Render all HUD elements to the window
    void draw(sf::RenderWindow& window) {
        timer.draw(window);
        collectables.draw(window);
    }

private:
    GameTimer timer;             ///< Countdown timer UI component
    HUDCollectables collectables;///< Collectables tracker UI component
};
