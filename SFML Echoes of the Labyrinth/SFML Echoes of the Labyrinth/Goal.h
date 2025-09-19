#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

enum class GoalState {
    Closed,
    Opening,
    Opened
};

class Goal {
public:
    Goal(sf::Vector2f size, sf::Vector2f position,
        const sf::Texture& closedTex, const sf::Texture& openTex);

    Goal(Goal&& other) noexcept;
    Goal& operator=(Goal&& other) noexcept;

    Goal(const Goal&) = delete;
    Goal& operator=(const Goal&) = delete;

    void update(float dt);
    void draw(sf::RenderWindow& window);
    Collider& getCollider();

    void open();
    bool isOpen() const;
    bool isFullyOpen() const;

    bool playerReached(const Collider& playerCollider) const;

private:
    sf::RectangleShape body;
    Collider collider;
   
    const sf::Texture* closedTexture;
    const sf::Texture* openTexture;
    Animation openAnim;

    GoalState state;
    bool openState;
};
