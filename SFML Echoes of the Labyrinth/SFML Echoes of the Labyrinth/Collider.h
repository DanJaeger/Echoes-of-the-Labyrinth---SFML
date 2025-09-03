#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
    explicit Collider(sf::RectangleShape* body) : body(body) {} //'explicit' is used to mark constructors to not implicitly convert types in C++

    bool checkCollision(Collider& other, float push);
    void move(float dx, float dy) { body->move(dx, dy); }

    sf::Vector2f getPosition() const { return body->getPosition(); }
    sf::Vector2f getHalfSize() const { return body->getSize() / 2.f; }

    void rebind(sf::RectangleShape* newBody) { body = newBody; }

private: 
    sf::RectangleShape* body;
};

