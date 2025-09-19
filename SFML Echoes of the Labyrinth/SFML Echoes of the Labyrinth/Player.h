#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "PlayerInput.h"
#include "Collider.h"
#include "Animation.h"

class Player {
public:
    Player();

    void update(float dt);

    void draw(sf::RenderWindow& window);

    // Getters / Setters
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

    Collider& getCollider();

private:
    void initHitbox();
    void initSprite();
    void initAnimation();
    void updateAnimation(sf::Vector2f velocity, float dt);
    void moveSpriteWithHitbox();

    sf::Sprite sprite;      
    sf::Vector2f velocity;   
    float speed;        

    sf::RectangleShape hitbox;
    Collider collider;
    PlayerInput input;

    Animation idleAnim;
    Animation walkAnim;
    Animation* currentAnim;

    bool faceRight;
    sf::Vector2f baseScale;
};


