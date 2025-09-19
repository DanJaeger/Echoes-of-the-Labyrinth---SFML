#include "HUDCollectables.h"

HUDCollectables::HUDCollectables()
    : total(0), collected(0), spacing(10.f), margin(0.f, 0.f)
{
    font = &ResourceManager::getInstance().getFont("clock.ttf");

    text.setFont(*font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2.f);
}

void HUDCollectables::setTotal(int totalCollectables) {
    total = totalCollectables;
    updateText();
}

void HUDCollectables::setCollected(int collectedCount) {
    collected = collectedCount;
    updateText();
}

void HUDCollectables::setIcon(const sf::Texture& texture) {
    icon.setTexture(texture);
    icon.setScale(2.f, 2.f); 
    updateLayout();
}

void HUDCollectables::setPosition(const sf::Vector2f& pos) {
    basePosition = pos;
    updateLayout();
}

void HUDCollectables::setSpacing(float space)
{
    spacing = space;
    updateLayout();
}

void HUDCollectables::setMargin(const sf::Vector2f& offset) {
    margin = offset;
    updateLayout();
}

void HUDCollectables::draw(sf::RenderWindow& window) {
    window.draw(icon);
    window.draw(text);
}

void HUDCollectables::updateText() {
    int remaining = total - collected;
    if (remaining < 0) remaining = 0;

    text.setString("x" + std::to_string(remaining));
}

void HUDCollectables::updateLayout() {
    sf::Vector2f pos = basePosition + margin;

    icon.setPosition(pos);

    float iconHeight = icon.getGlobalBounds().height;
    float textHeight = text.getLocalBounds().height;

    float yOffset = (iconHeight - textHeight) / 2.f - text.getLocalBounds().top;

    text.setPosition(
        pos.x + icon.getGlobalBounds().width + spacing,
        pos.y + yOffset
    );
}
