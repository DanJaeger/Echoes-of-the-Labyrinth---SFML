#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    Game()
        : window(sf::VideoMode(640, 480), "Echoes of the Labyrinth")
    {
        window.setFramerateLimit(60);
    }

    void run() {
        sf::Clock clock;

        while (window.isOpen()) {
            processEvents();

            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Event event;

    void processEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update(float deltaTime) {
        std::cout << "Elapsed time since previous frame (seconds): "
            << deltaTime << std::endl;
    }

    void render() {
        window.clear();

        // Draw whatever you want

        window.display();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}