#pragma once
#include <SFML/Graphics.hpp>
#include "GameTimer.h"
#include "HUDCollectables.h"

class HUD {
public:
    HUD() = default;

    void setFont(sf::Font& font) {
        timer.setFont(font);
    }

    void setTimerStyle(unsigned int size, sf::Color fill, sf::Color outline, float thickness) {
        timer.setCharacterSize(size);
        timer.setColors(fill, outline, thickness);
    }

    void setTimerPosition(const sf::Vector2f& pos) {
        timer.setPosition(pos);
    }

    void setOnTimeout(std::function<void()> callback) {
        timer.setOnTimeout(callback);
    }

    void startTimer(sf::Time duration) {
        timer.start(duration);
    }

    void setMargin(const sf::Vector2f& margin) {
        timer.setMargin(margin);
        collectables.setMargin(margin);
    }

    void setCollectablesSpacing(float space) {
        collectables.setSpacing(space);
    }

    void setCollectablesTotal(int total) {
        collectables.setTotal(total);
    }

    void setCollectablesCollected(int collected) {
        collectables.setCollected(collected);
    }

    void setCollectablesIcon(const sf::Texture& texture) {
        collectables.setIcon(texture);
    }

    void setCollectablesPosition(const sf::Vector2f& pos) {
        collectables.setPosition(pos);
    }

    void update(int collectedCount) {
        setCollectablesCollected(collectedCount);
        timer.update();
    }

    void draw(sf::RenderWindow& window) {
        timer.draw(window);
        collectables.draw(window);
    }

private:
    GameTimer timer;
    HUDCollectables collectables;
};
