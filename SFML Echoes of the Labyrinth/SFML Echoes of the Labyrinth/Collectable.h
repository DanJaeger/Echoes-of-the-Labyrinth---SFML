#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Collectable {
public:
    Collectable(sf::Vector2f size, sf::Vector2f position, const sf::Texture& texture);

    Collectable(Collectable&& other) noexcept;
    Collectable& operator=(Collectable&& other) noexcept;

    Collectable(const Collectable&) = delete;
    Collectable& operator=(const Collectable&) = delete;

    void draw(sf::RenderWindow& window);
    Collider& getCollider();

    bool isCollected() const;
    void collect();

private:
    sf::RectangleShape body;
    Collider collider;
    bool collected;
};
