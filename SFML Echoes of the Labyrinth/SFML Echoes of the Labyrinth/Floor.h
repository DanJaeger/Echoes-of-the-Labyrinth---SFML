#pragma once
#include <SFML/Graphics.hpp>

class Floor
{
public:
    Floor(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

    Floor(Floor&& other) noexcept;
    Floor& operator=(Floor&& other) noexcept;

    Floor(const Floor&) = delete;
    Floor& operator=(const Floor&) = delete;

    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape body;
};
