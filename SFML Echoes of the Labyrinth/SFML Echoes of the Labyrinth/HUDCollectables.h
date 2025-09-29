#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"

/**
 * @brief Displays the collectables counter in the HUD.
 *
 * This component shows an icon and the number of collectables
 * remaining for the player to gather.
 */
class HUDCollectables {
public:
    HUDCollectables();

    /// Set the total number of collectables in the level
    void setTotal(int totalCollectables);

    /// Update the number of collectables already collected
    void setCollected(int collectedCount);

    /// Assign the texture/icon for collectables
    void setIcon(const sf::Texture& texture);

    /// Define the base position for the UI element
    void setPosition(const sf::Vector2f& pos);

    /// Set spacing between icon and text
    void setSpacing(float space);

    /// Apply a margin offset to position
    void setMargin(const sf::Vector2f& offset);

    /// Draw the collectables UI on the render window
    void draw(sf::RenderWindow& window);

private:
    const sf::Font* font; ///< Pointer to shared font resource
    sf::Text text;        ///< Text displaying remaining collectables
    sf::Sprite icon;      ///< Sprite representing collectable item

    int total;            ///< Total collectables in the level
    int collected;        ///< Collected count so far

    float spacing;        ///< Spacing between icon and text
    sf::Vector2f basePosition; ///< Base position for layout
    sf::Vector2f margin;       ///< Margin offset

    /// Update the displayed text based on current collected/total
    void updateText();

    /// Update layout and positions of icon + text
    void updateLayout();
};
