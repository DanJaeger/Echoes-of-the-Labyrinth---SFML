#include "Labyrinth.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "Config.h"
#include <iostream>
#include <stack>
#include <random>

// Constructor: initializes RNG and loads all textures
Labyrinth::Labyrinth()
    : rng(std::random_device{}()), numberOfCollectables(Config::Labyrinth::NUMBER_OF_COLLECTABLES)
{
    loadTextures();
}

// Update labyrinth state (collisions, collectables, goal animations, etc.)
void Labyrinth::update(float dt, Player& player) {
    handleCollisions(player);

    if (goal.has_value()) {
        goal->update(dt);
    }

    for (auto& collectable : collectables)
        collectable.update(dt);
}

// Generate a new labyrinth based on window size and cell pixel size
void Labyrinth::generate(sf::Vector2u windowSize, unsigned cellPixelSize) {
    cols = windowSize.x / cellPixelSize;
    rows = windowSize.y / cellPixelSize;

    cellSize = {
        static_cast<float>(windowSize.x) / cols,
        static_cast<float>(windowSize.y) / rows
    };

    reset(windowSize);
}

// Reset labyrinth (clear structures and generate a new one)
void Labyrinth::reset(sf::Vector2u windowSize) {
    walls.clear();
    floors.clear();
    grid.clear();

    collectedKeys = 0;

    generateMazeDFS(rows, cols, cellSize);
}

// Returns total number of collectables
int Labyrinth::getCollectablesCount() const { return numberOfCollectables; }

// Returns number of collected items so far
int Labyrinth::getCollectedCount() const { return collectedKeys; }

// Returns spawn point for player
sf::Vector2f Labyrinth::getSpawnPoint() const {
    return { cellSize.x / Config::Labyrinth::SPAWN_OFFSET, cellSize.y / Config::Labyrinth::SPAWN_OFFSET };
}

// Assigns callback when the player wins
void Labyrinth::setOnWin(std::function<void()> callback) { onWin = callback; }

// Draw all labyrinth elements
void Labyrinth::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& floor : floors) floor.draw(window);
    for (auto& wall : walls) wall.draw(window);
    for (auto& collectable : collectables) collectable.draw(window);

    if (goal.has_value())
        goal->draw(window);
}

// Handles all collisions (walls, collectables, goal)
void Labyrinth::handleCollisions(Player& player) {
    // Collisions with walls
    for (auto& wall : walls) {
        player.getCollider().checkCollision(wall.getCollider(), Config::Labyrinth::COLLISION_PUSH);
    }

    // Collisions with collectables
    for (auto& collectable : collectables) {
        if (!collectable.isCollected() &&
            player.getCollider().checkCollision(collectable.getCollider(), Config::Labyrinth::COLLISION_PUSH))
        {
            collectable.collect();
            collectedKeys++;
            AudioManager::getInstance().playSound(Config::Audio::SOUND_PICKUP);
            std::cout << Config::Debug::COLLECTABLE_PICKUP << std::endl;
        }
    }

    // Open goal if all collectables are taken
    if (goal.has_value() && collectedKeys >= numberOfCollectables && !goal->isOpen()) {
        goal->open();
        std::cout << Config::Debug::GOAL_OPEN << std::endl;
        AudioManager::getInstance().playSound(Config::Audio::SOUND_OPEN_CHEST);
    }

    // Check if player reached the goal
    if (goal.has_value() && goal->playerReached(player.getCollider()) && goal->isOpen()) {
        std::cout << Config::Debug::PLAYER_WIN << std::endl;
        if (onWin) onWin();
    }
}

// DFS algorithm to generate labyrinth procedurally
void Labyrinth::generateMazeDFS(size_t rows, size_t cols, sf::Vector2f cellSize) {
    // Initialize grid as walls
    grid.assign(rows, std::vector<CellType>(cols, CellType::Wall));

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // DFS parameters
    constexpr int CELL_JUMP = Config::Labyrinth::CELL_JUMP;
    constexpr float BORDER_THICKNESS = Config::Labyrinth::BORDER_THICKNESS;

    // Possible moves: up, down, left, right
    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    std::random_device rd;
    std::mt19937 gen(rd());

    // DFS using a stack
    std::stack<std::pair<int, int>> st;
    st.push({ 0, 0 });
    visited[0][0] = true;
    grid[0][0] = CellType::Empty;

    while (!st.empty()) {
        auto [r, c] = st.top();

        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::shuffle(dirs.begin(), dirs.end(), gen);

        bool moved = false;
        for (int d : dirs) {
            int nr = r + dr[d] * CELL_JUMP;
            int nc = c + dc[d] * CELL_JUMP;

            // If new cell is valid and not visited
            if (nr >= 0 && nc >= 0 && nr < (int)rows && nc < (int)cols && !visited[nr][nc]) {
                // Open intermediate cell
                int wr = r + dr[d];
                int wc = c + dc[d];

                grid[wr][wc] = CellType::Empty;
                grid[nr][nc] = CellType::Empty;

                visited[nr][nc] = true;
                st.push({ nr, nc });
                moved = true;
                break;
            }
        }

        if (!moved) st.pop(); // backtrack if no moves
    }

    // Post-process: ensure all non-path cells are walls
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            if (grid[r][c] != CellType::Empty && grid[r][c] != CellType::Goal) {
                grid[r][c] = CellType::Wall;
            }
        }
    }

    // Build graphical objects
    generateFromGrid(grid, cellSize);

    // Generate collectables
    collectables.clear();
    std::vector<sf::Vector2f> emptyCells;

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            if (grid[r][c] == CellType::Empty) {
                emptyCells.push_back({
                    c * cellSize.x + cellSize.x / 2,
                    r * cellSize.y + cellSize.y / 2
                    });
            }
        }
    }

    std::shuffle(emptyCells.begin(), emptyCells.end(), rng);

    // Place collectables in random free cells
    for (int i = 0; i < numberOfCollectables && i < (int)emptyCells.size(); i++) {
        collectables.emplace_back(
            sf::Vector2f(cellSize.x * Config::Collectables::SCALE, cellSize.y * Config::Collectables::SCALE),
            emptyCells[i], *collectableTexture
        );
    }

    // Place goal near the center of the labyrinth
    if (!emptyCells.empty()) {
        sf::Vector2f center(cols * cellSize.x / 2, rows * cellSize.y / 2);

        std::sort(emptyCells.begin(), emptyCells.end(),
            [center](const sf::Vector2f& a, const sf::Vector2f& b) {
                float da = std::hypot(a.x - center.x, a.y - center.y);
                float db = std::hypot(b.x - center.x, b.y - center.y);
                return da < db;
            });

        sf::Vector2f goalPos = emptyCells.front();

        goal.emplace(
            sf::Vector2f(cellSize.x * Config::Collectables::SCALE, cellSize.y * Config::Collectables::SCALE),
            goalPos, *goalClosedTexture, *goalOpenTexture
        );
    }

    // Add external border walls
    addBorderWalls(cols * cellSize.x, rows * cellSize.y, BORDER_THICKNESS);
}

// Converts grid into graphical objects (walls/floors)
void Labyrinth::generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize) {
    grid = layout;
    walls.clear();
    floors.clear();

    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            sf::Vector2f pos(col * cellSize.x + cellSize.x / 2,
                row * cellSize.y + cellSize.y / 2);

            sf::Vector2f size(cellSize.x, cellSize.y);

            switch (grid[row][col]) {
            case CellType::Wall:
                walls.emplace_back(size, pos, *wallTexture);
                break;
            case CellType::Goal:
                // TODO: implement if needed (fixed goal position)
                break;
            case CellType::Empty:
                floors.emplace_back(size, pos, *floorTexture);
                break;
            default:
                break;
            }
        }
    }
}

// Add border walls around the labyrinth
void Labyrinth::addBorderWalls(float width, float height, float thickness) {
    // TOP
    walls.emplace_back(sf::Vector2f(width, thickness),
        sf::Vector2f(width / 2, thickness / 2), *borderTexture);

    // BOTTOM
    walls.emplace_back(sf::Vector2f(width, thickness),
        sf::Vector2f(width / 2, height - thickness / 2), *borderTexture);

    // LEFT
    walls.emplace_back(sf::Vector2f(thickness, height),
        sf::Vector2f(thickness / 2, height / 2), *borderTexture);

    // RIGHT
    walls.emplace_back(sf::Vector2f(thickness, height),
        sf::Vector2f(width - thickness / 2, height / 2), *borderTexture);
}

// Load all labyrinth textures
void Labyrinth::loadTextures() {
    borderTexture = &ResourceManager::getInstance().getTexture(Config::Labyrinth::BORDER_TEXTURE);
    wallTexture = &ResourceManager::getInstance().getTexture(Config::Labyrinth::WALL_TEXTURE);
    floorTexture = &ResourceManager::getInstance().getTexture(Config::Labyrinth::FLOOR_TEXTURE);

    collectableTexture = &ResourceManager::getInstance().getTexture(Config::Collectables::TEXTURE);

    goalClosedTexture = &ResourceManager::getInstance().getTexture(Config::Goal::TEXTURE_CLOSED);
    goalOpenTexture = &ResourceManager::getInstance().getTexture(Config::Goal::TEXTURE_OPEN);
}
