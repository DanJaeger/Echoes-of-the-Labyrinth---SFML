#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

/**
 * @brief Global configuration constants for the game.
 * Organized by namespaces to avoid magic numbers and improve modularity.
 */
namespace Config {

    // ---------------- Resource Manager ----------------
    namespace Resources {
        inline const std::string TEXTURE_PATH = "assets/textures/";
        inline const std::string FONT_PATH = "assets/fonts/";
    }

    // ---------------- Game Window ----------------
    namespace Window {
        static constexpr unsigned int FPS = 60;
    }

    // ---------------- Animation ----------------
    namespace Animation {
        inline const std::string DEFAULT_TEXTURE_PATH = "assets/textures/";
        inline constexpr float SWITCH_TIME = 0.15f; // Seconds between frames
    }

    // ---------------- Player ----------------
    namespace Player {
        inline const float SPEED = 200.f;
        inline constexpr float DIAGONAL_NORMALIZER = 1.4142135f; // sqrt(2)

        // Hitbox
        inline const sf::Vector2f HITBOX_SIZE = { 25.f, 25.f };
        inline const sf::Color HITBOX_FILL = sf::Color::Transparent;
        inline const sf::Color HITBOX_OUTLINE = sf::Color::Red;
        inline const float HITBOX_OUTLINE_THICKNESS = 1.f;
        inline const sf::Vector2f START_POSITION = { 100.f, 100.f };

        // Sprite
        inline const sf::Vector2f BASE_SCALE = { 1.5f, 1.5f };

        // Animations
        inline const float IDLE_FRAME_TIME = 0.15f;
        inline const float WALK_FRAME_TIME = 0.1f;

        inline const std::vector<std::string> IDLE_FRAMES = {
            "player/idle_0.png",
            "player/idle_1.png",
            "player/idle_2.png",
            "player/idle_3.png"
        };

        inline const std::vector<std::string> WALK_FRAMES = {
            "player/run_0.png",
            "player/run_1.png",
            "player/run_2.png",
            "player/run_3.png"
        };
    }

    // ---------------- Labyrinth ----------------
    namespace Labyrinth {
        // Cell and wall settings
        inline constexpr unsigned CELL_PIXEL_SIZE = 32;
        inline constexpr int CELL_JUMP = 2;
        inline constexpr float BORDER_THICKNESS = 10.f;
        inline constexpr int NUMBER_OF_COLLECTABLES = 4;

        // Spawn offset
        inline constexpr float SPAWN_OFFSET = 2.f;

        // Collision
        inline constexpr float COLLISION_PUSH = 0.0f;

        // Textures
        inline const std::string BORDER_TEXTURE = "tiles/border.png";
        inline const std::string WALL_TEXTURE = "tiles/wall.png";
        inline const std::string FLOOR_TEXTURE = "tiles/floor.png";
    }

    // ---------------- Walls ----------------
    namespace Walls {
        inline constexpr int TEXTURE_OFFSET_X = 0;
        inline constexpr int TEXTURE_OFFSET_Y = 0;
    }

    // ---------------- Timer ----------------
    namespace Timer {
        static constexpr unsigned int FONT_SIZE = 24;
        static constexpr float OUTLINE_THICKNESS = 2.f;
        inline const sf::Vector2f DEFAULT_POSITION = { 10.f, 10.f };
        inline const sf::Vector2f DEFAULT_MARGIN = { 0.f, 0.f };
        inline const std::string FONT = "clock.ttf";
    }

    // ---------------- Collectables ----------------
    namespace Collectables {
        static constexpr float FLOAT_SPEED = 5.f;
        static constexpr float FLOAT_HEIGHT = 2.f;
        inline const std::string TEXTURE = "items/collectable.png";
        inline constexpr float SCALE = 0.6f;
    }

    // ---------------- Goal (Chest) ----------------
    namespace Goal {
        static constexpr float ANIM_FRAME_TIME = 0.2f;

        inline const std::string FRAME_1 = "items/chest_empty_0.png";
        inline const std::string FRAME_2 = "items/chest_empty_1.png";
        inline const std::string FRAME_3 = "items/chest_full_open.png";

        inline const std::string TEXTURE_CLOSED = "items/chest_empty_0.png";
        inline const std::string TEXTURE_OPEN = "items/chest_full_open.png";

        inline constexpr float SCALE = 0.8f;
    }

    // ---------------- HUD ----------------
    namespace HUD {
        static constexpr unsigned int FONT_SIZE = 24;
        static constexpr float OUTLINE_THICKNESS = 2.f;

        inline const sf::Vector2f TIMER_POSITION = { 0.f, 0.f };
        inline const sf::Vector2f COLLECTABLES_POSITION = { 0.f, 30.f };
        inline const sf::Vector2f MARGIN = { 15.f, 15.f };

        namespace Collectables {
            inline constexpr unsigned int FONT_SIZE = 24;
            inline constexpr float OUTLINE_THICKNESS = 2.f;
            inline constexpr float SPACING = 10.f;
            inline constexpr float ICON_SCALE = 2.f;

            inline const sf::Color FONT_COLOR = sf::Color::White;
            inline const sf::Color OUTLINE_COLOR = sf::Color::Black;
            inline const sf::Vector2f DEFAULT_MARGIN = { 0.f, 0.f };
        }
    }

    // ---------------- Menu ----------------
    namespace Menu {
        // General text
        inline const std::string FONT = "clock.ttf";
        inline const std::string TITLE = "Echoes of the Labyrinth";
        inline const unsigned TITLE_CHAR_SIZE = 48;
        inline const unsigned OPTION_CHAR_SIZE = 32;
        inline const std::string TEXT_PAUSE_TITLE = "Pause";
        inline const std::string TEXT_LOSE_TITLE = "You Lost";
        inline const std::string TEXT_WIN_TITLE = "You Won!";
        inline const std::string TEXT_OPTION_START = "Start";
        inline const std::string TEXT_OPTION_RESTART = "Restart";
        inline const std::string TEXT_OPTION_QUIT = "Quit";

        // Menu option indices
        inline constexpr int OPTION_RESTART = 0;
        inline constexpr int OPTION_QUIT = 1;

        // Colors
        inline const sf::Color TITLE_COLOR = sf::Color::Yellow;
        inline const sf::Color SELECTED_OPTION_COLOR = sf::Color::Cyan;
        inline const sf::Color UNSELECTED_OPTION_COLOR = sf::Color::White;
        inline const sf::Color OVERLAY_COLOR = sf::Color(0, 0, 0, 150);

        // Positions and spacing
        inline const float TITLE_POS_X = 100.f;
        inline const float TITLE_POS_Y = 100.f;
        inline const float OPTION_START_Y = 250.f;
        inline const float OPTION_OFFSET_X = 120.f;
        inline const float OPTION_SPACING = 50.f;
    }

    // ---------------- Audio ----------------
    namespace Audio {
        static constexpr float MUSIC_VOLUME = 40.f;
        static constexpr float SFX_VOLUME = 100.f;

        inline const std::string SOUND_PICKUP = "pickup";
        inline const std::string SOUND_OPEN_CHEST = "openChest";
    }

    // ---------------- Gameplay ----------------
    namespace Gameplay {
        static constexpr int TIME_LIMIT_SECONDS = 240; // 4 minutes
    }

    // ---------------- Debug Messages ----------------
    namespace Debug {
        inline const std::string COLLECTABLE_PICKUP = "Collectable collected!";
        inline const std::string GOAL_OPEN = "The door is now open!";
        inline const std::string PLAYER_WIN = "YOU WIN!";
    }

} // namespace Config
