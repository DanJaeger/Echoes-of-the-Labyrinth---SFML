#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * @class MenuScreen
 * @brief A generic menu screen that can display a title and a list of selectable options.
 */
class MenuScreen {
public:
    MenuScreen(sf::RenderWindow& window, sf::Font& font, bool useOverlay = false);

    void setTitle(const std::string& title);
    void setOptions(const std::vector<std::string>& options);

    void processEvent(const sf::Event& ev);
    void draw();

    int pollSelectedOption();
    void reset();

private:
    sf::RenderWindow& window;
    sf::Font& font;

    sf::Text titleText;
    std::vector<sf::Text> optionTexts;

    sf::RectangleShape overlay;
    bool useOverlay;

    int selectedIndex;
    int chosenOption;

    void updateVisuals();
    void centerTexts();
};
