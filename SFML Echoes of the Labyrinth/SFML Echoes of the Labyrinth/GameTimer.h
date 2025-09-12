#pragma once
#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <SFML/Graphics.hpp>
#include <functional>

class GameTimer {
public:
    GameTimer();

    void start(sf::Time limit);
    void reset();
    void update(); 
    void draw(sf::RenderWindow& window);

    void setFont(const sf::Font& font);
    void setPosition(const sf::Vector2f& pos);
    void setCharacterSize(unsigned int size);
    void setColors(sf::Color fill, sf::Color outline = sf::Color::Black, float thickness = 2.f);

    void setOnTimeout(std::function<void()> callback);

private:
    sf::Clock clock;
    sf::Time timeLimit;
    bool running = false;

    sf::Text text;

    std::function<void()> onTimeout;
};

#endif


