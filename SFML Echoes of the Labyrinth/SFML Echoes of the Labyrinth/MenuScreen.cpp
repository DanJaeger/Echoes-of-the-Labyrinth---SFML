#include "MenuScreen.h"
#include "Config.h"

MenuScreen::MenuScreen(sf::RenderWindow& window, sf::Font& font, bool useOverlay)
    : window(window), font(font), selectedIndex(0), chosenOption(-1), useOverlay(useOverlay)
{
    // Setup title text
    titleText.setFont(font);
    titleText.setCharacterSize(Config::Menu::TITLE_CHAR_SIZE);
    titleText.setFillColor(Config::Menu::TITLE_COLOR);

    // Setup overlay if needed
    if (useOverlay) {
        overlay.setSize(sf::Vector2f(window.getSize()));
        overlay.setFillColor(Config::Menu::OVERLAY_COLOR);
    }
}

/**
 * @brief Set the title text and its position depending on overlay usage.
 */
void MenuScreen::setTitle(const std::string& title) {
    titleText.setString(title);
    if (useOverlay) {
        sf::FloatRect bounds = titleText.getLocalBounds();
        titleText.setOrigin(bounds.width / 2.f, 0.f);
        titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 4.f);
    }
    else {
        titleText.setPosition(Config::Menu::TITLE_POS_X, Config::Menu::TITLE_POS_Y);
    }
}

/**
 * @brief Set menu options and position them on the screen.
 */
void MenuScreen::setOptions(const std::vector<std::string>& options) {
    optionTexts.clear();

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(Config::Menu::OPTION_CHAR_SIZE);
        optionTexts.push_back(text);
    }

    if (useOverlay) {
        centerTexts();
    }
    else {
        for (size_t i = 0; i < optionTexts.size(); i++) {
            optionTexts[i].setPosition(
                Config::Menu::OPTION_OFFSET_X,
                Config::Menu::OPTION_START_Y + i * Config::Menu::OPTION_SPACING
            );
        }
    }

    updateVisuals();
}

/**
 * @brief Center menu options vertically and horizontally on screen.
 */
void MenuScreen::centerTexts() {
    float totalHeight = optionTexts.size() * Config::Menu::OPTION_SPACING;
    float startY = (window.getSize().y / 2.f) - (totalHeight / 2.f);

    for (size_t i = 0; i < optionTexts.size(); i++) {
        sf::FloatRect bounds = optionTexts[i].getLocalBounds();
        optionTexts[i].setOrigin(bounds.width / 2.f, 0.f);
        optionTexts[i].setPosition(window.getSize().x / 2.f, startY + i * Config::Menu::OPTION_SPACING);
    }
}

/**
 * @brief Handle keyboard input to navigate through menu options.
 */
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

/**
 * @brief Draw the menu elements (overlay, title, options).
 */
void MenuScreen::draw() {
    if (useOverlay) {
        window.draw(overlay);
    }

    window.draw(titleText);
    for (auto& opt : optionTexts)
        window.draw(opt);
}

/**
 * @brief Poll and reset the last selected option.
 * @return Index of the chosen option, or -1 if none selected.
 */
int MenuScreen::pollSelectedOption() {
    int opt = chosenOption;
    chosenOption = -1;
    return opt;
}

/**
 * @brief Reset selection to the first option.
 */
void MenuScreen::reset() {
    selectedIndex = 0;
    chosenOption = -1;
    updateVisuals();
}

/**
 * @brief Update the color of menu options to reflect selection.
 */
void MenuScreen::updateVisuals() {
    for (size_t i = 0; i < optionTexts.size(); i++) {
        if ((int)i == selectedIndex)
            optionTexts[i].setFillColor(Config::Menu::SELECTED_OPTION_COLOR);
        else
            optionTexts[i].setFillColor(Config::Menu::UNSELECTED_OPTION_COLOR);
    }
}
