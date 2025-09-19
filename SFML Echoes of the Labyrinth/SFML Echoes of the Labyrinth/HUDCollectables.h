#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class HUDCollectables {
public:
    HUDCollectables();

    void setTotal(int totalCollectables);
    void setCollected(int collectedCount);

    void setIcon(const sf::Texture& texture);
    void setPosition(const sf::Vector2f& pos);
    void setSpacing(float space);
    void setMargin(const sf::Vector2f& offset);

    void draw(sf::RenderWindow& window);

private:
    const sf::Font* font;
    sf::Text text;
    sf::Sprite icon;

    int total;
    int collected;

    float spacing;
    sf::Vector2f basePosition;
    sf::Vector2f margin;

    void updateText();
    void updateLayout();
};
