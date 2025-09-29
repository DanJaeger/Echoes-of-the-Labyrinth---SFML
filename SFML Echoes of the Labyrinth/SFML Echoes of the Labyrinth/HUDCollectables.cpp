#include "HUDCollectables.h"

HUDCollectables::HUDCollectables()
    : total(0),
    collected(0),
    spacing(Config::HUD::Collectables::SPACING),
    margin(Config::HUD::MARGIN)
{
    // Load shared font from ResourceManager
    font = &ResourceManager::getInstance().getFont("clock.ttf");

    // Configure text style and appearance
    text.setFont(*font);
    text.setCharacterSize(Config::HUD::FONT_SIZE);
    text.setFillColor(Config::HUD::Collectables::FONT_COLOR);
    text.setOutlineColor(Config::HUD::Collectables::OUTLINE_COLOR);
    text.setOutlineThickness(Config::HUD::Collectables::OUTLINE_THICKNESS);
}

void HUDCollectables::setTotal(int totalCollectables) {
    // Store total collectables for the current level
    total = totalCollectables;

    // Update displayed text (xN)
    updateText();
}

void HUDCollectables::setCollected(int collectedCount) {
    // Store number of collectables already gathered
    collected = collectedCount;

    // Update displayed text (xN)
    updateText();
}

void HUDCollectables::setIcon(const sf::Texture& texture) {
    // Assign the texture for the collectable icon
    icon.setTexture(texture);

    // Scale for better visibility (uses Config constant)
    icon.setScale(Config::HUD::Collectables::ICON_SCALE,
        Config::HUD::Collectables::ICON_SCALE);

    // Recalculate layout after updating icon
    updateLayout();
}

void HUDCollectables::setPosition(const sf::Vector2f& pos) {
    // Define the base position for the entire HUD element
    basePosition = pos;

    // Recalculate positions of text and icon
    updateLayout();
}

void HUDCollectables::setSpacing(float space) {
    // Define horizontal spacing between icon and text
    spacing = space;

    // Recalculate layout with new spacing
    updateLayout();
}

void HUDCollectables::setMargin(const sf::Vector2f& offset) {
    // Apply additional margin offset from base position
    margin = offset;

    // Recalculate layout with new margin
    updateLayout();
}

void HUDCollectables::draw(sf::RenderWindow& window) {
    // Draw icon first, then the text on top
    window.draw(icon);
    window.draw(text);
}

void HUDCollectables::updateText() {
    // Calculate remaining collectables (never go below 0)
    int remaining = total - collected;
    if (remaining < 0) remaining = 0;

    // Format text as: xN
    text.setString("x" + std::to_string(remaining));
}

void HUDCollectables::updateLayout() {
    // Start from base position + margin offset
    sf::Vector2f pos = basePosition + margin;

    // Place icon at computed position
    icon.setPosition(pos);

    // Align text vertically centered with the icon
    float iconHeight = icon.getGlobalBounds().height;
    float textHeight = text.getLocalBounds().height;

    // Adjustment for baseline/top offset of the font
    float yOffset = (iconHeight - textHeight) / 2.f - text.getLocalBounds().top;

    // Place text to the right of the icon with spacing
    text.setPosition(
        pos.x + icon.getGlobalBounds().width + spacing,
        pos.y + yOffset
    );
}
