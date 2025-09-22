#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& window, sf::Font& font, bool useOverlay)
    : window(window), font(font), selectedIndex(0), chosenOption(-1), useOverlay(useOverlay)
{
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Yellow);

    if (useOverlay) {
        overlay.setSize(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
    }
}

void MenuScreen::setTitle(const std::string& title) {
    titleText.setString(title);
    if (useOverlay) {
        sf::FloatRect bounds = titleText.getLocalBounds();
        titleText.setOrigin(bounds.width / 2.f, 0.f);
        titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 4.f);
    }
    else {
        titleText.setPosition(100.f, 100.f);
    }
}

void MenuScreen::setOptions(const std::vector<std::string>& options) {
    optionTexts.clear();
    float spacing = 50.f;

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(32);
        optionTexts.push_back(text);
    }

    if (useOverlay) {
        centerTexts();
    }
    else {
        float startY = 250.f;
        for (size_t i = 0; i < optionTexts.size(); i++) {
            optionTexts[i].setPosition(120.f, startY + i * spacing);
        }
    }

    updateVisuals();
}

void MenuScreen::centerTexts() {
    float spacing = 50.f;
    float totalHeight = optionTexts.size() * spacing;
    float startY = (window.getSize().y / 2.f) - (totalHeight / 2.f);

    for (size_t i = 0; i < optionTexts.size(); i++) {
        sf::FloatRect bounds = optionTexts[i].getLocalBounds();
        optionTexts[i].setOrigin(bounds.width / 2.f, 0.f);
        optionTexts[i].setPosition(window.getSize().x / 2.f, startY + i * spacing);
    }
}

void MenuScreen::processEvent(const sf::Event& ev) {
    if (ev.type != sf::Event::KeyPressed) return;

    if (ev.key.code == sf::Keyboard::Up) {
        selectedIndex = (selectedIndex - 1 + (int)optionTexts.size()) % (int)optionTexts.size();
        updateVisuals();
    }
    else if (ev.key.code == sf::Keyboard::Down) {
        selectedIndex = (selectedIndex + 1) % (int)optionTexts.size();
        updateVisuals();
    }
    else if (ev.key.code == sf::Keyboard::Enter) {
        chosenOption = selectedIndex;
    }
}

void MenuScreen::draw() {
    if (useOverlay) {
        window.draw(overlay);
    }

    window.draw(titleText);
    for (auto& opt : optionTexts)
        window.draw(opt);
}

int MenuScreen::pollSelectedOption() {
    int opt = chosenOption;
    chosenOption = -1; 
    return opt;
}

void MenuScreen::reset() {
    selectedIndex = 0;
    chosenOption = -1;
    updateVisuals();
}

void MenuScreen::updateVisuals() {
    for (size_t i = 0; i < optionTexts.size(); i++) {
        if ((int)i == selectedIndex)
            optionTexts[i].setFillColor(sf::Color::Cyan);
        else
            optionTexts[i].setFillColor(sf::Color::White);
    }
}
