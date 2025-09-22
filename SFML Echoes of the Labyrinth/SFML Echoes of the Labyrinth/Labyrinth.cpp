#include "Labyrinth.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include <iostream>
#include <stack>
#include <random>

Labyrinth::Labyrinth()
    : rng(std::random_device{}()) ,numberOfCollectables(4)
{
    loadTextures();
}

void Labyrinth::update(float dt, Player& player) {
    handleCollisions(player);

    if (goal.has_value()) {
        goal->update(dt);
    }

    for (auto& collectable : collectables)
        collectable.update(dt);
    
}

void Labyrinth::generate(sf::Vector2u windowSize, unsigned cellPixelSize) {
    cols = windowSize.x / cellPixelSize;
    rows = windowSize.y / cellPixelSize;

    cellSize = {
        static_cast<float>(windowSize.x) / cols,
        static_cast<float>(windowSize.y) / rows
    };

    reset(windowSize);
}

void Labyrinth::reset(sf::Vector2u windowSize) {
    walls.clear();
    floors.clear();
    grid.clear();

    collectedKeys = 0;

    generateMazeDFS(rows, cols, cellSize);
}

int Labyrinth::getCollectablesCount() const
{
    return numberOfCollectables;
}

int Labyrinth::getCollectedCount() const
{
    return collectedKeys;
}

sf::Vector2f Labyrinth::getSpawnPoint() const {
    return {
        cellSize.x / 2.f,
        cellSize.y / 2.f
    };
}

void Labyrinth::setOnWin(std::function<void()> callback)
{
    onWin = callback;
}

void Labyrinth::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& floor : floors)
        floor.draw(window);

    for (auto& wall : walls)
        wall.draw(window);

    for (auto& collectable : collectables) 
        collectable.draw(window);

    if (goal.has_value())
        goal->draw(window);
}

void Labyrinth::handleCollisions(Player& player) 
{
    for (auto& wall : walls) {
        player.getCollider().checkCollision(wall.getCollider(), 0.0f);
    }

    for (auto& collectable : collectables) {
        if (!collectable.isCollected() &&
            player.getCollider().checkCollision(collectable.getCollider(), 0.0f))
        {
            collectable.collect();
            collectedKeys++;
            AudioManager::getInstance().playSound("pickup");
            std::cout << "collectable collected!" << std::endl;
        }
    }

    // Abrir goal si ya tiene todas las llaves
    if (goal.has_value() && collectedKeys >= numberOfCollectables && !goal->isOpen()) {
        goal->open();
        std::cout << "The door is now open!" << std::endl;
        AudioManager::getInstance().playSound("openChest");
    }

    // Verificar si jugador llega al goal
    if (goal.has_value() && goal->playerReached(player.getCollider()) && goal->isOpen()) {
        std::cout << "YOU WIN!" << std::endl;
        if (onWin) onWin();
    }

}

void Labyrinth::generateMazeDFS(size_t rows, size_t cols, sf::Vector2f cellSize)
{
    // 1. Initialize everything as walls
    grid.assign(rows, std::vector<CellType>(cols, CellType::Wall));

    // 2. Aux Variables 
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    constexpr int CELL_JUMP = 2;
    constexpr float BORDER_THICKNESS = 10.f;

    //Posible movements (up, down, left, right)
    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    // Random engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // 3. DFS using stack
    std::stack<std::pair<int, int>> st;
    st.push({ 0, 0 }); // start upper left
    visited[0][0] = true;
    grid[0][0] = CellType::Empty;

    while (!st.empty()) {
        auto [r, c] = st.top();

        // get neighbours not visited
        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::shuffle(dirs.begin(), dirs.end(), gen);

        bool moved = false;
        for (int d : dirs) {
            int nr = r + dr[d] * CELL_JUMP; // jump 2 cells
            int nc = c + dc[d] * CELL_JUMP;

            if (nr >= 0 && nc >= 0 && nr < (int)rows && nc < (int)cols && !visited[nr][nc]) {
                // middle cell (between current and new)
                int wr = r + dr[d];
                int wc = c + dc[d];

                // Opening path
                grid[wr][wc] = CellType::Empty;
                grid[nr][nc] = CellType::Empty;

                visited[nr][nc] = true;
                st.push({ nr, nc });
                moved = true;
                break;
            }
        }

        if (!moved) {
            st.pop(); // go back
        }
    }

    // Postprocessing
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            if (grid[r][c] != CellType::Empty && grid[r][c] != CellType::Goal) {
                grid[r][c] = CellType::Wall;
            }
        }
    }

    // 4. Converting grid into walls
    generateFromGrid(grid, cellSize);

    //5. Adding collectables
    collectables.clear();
    std::vector<sf::Vector2f> emptyCells;

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            if (grid[r][c] == CellType::Empty) {
                emptyCells.push_back({
                    c * cellSize.x + cellSize.x / 2.f,
                    r * cellSize.y + cellSize.y / 2.f
                    });
            }
        }
    }

    std::shuffle(emptyCells.begin(), emptyCells.end(), rng);

    // reserve number of collectables
    for (int i = 0; i < numberOfCollectables && i < (int)emptyCells.size(); i++) {
        collectables.emplace_back(sf::Vector2f(cellSize.x * 0.6f, cellSize.y * 0.6f),
            emptyCells[i],
            *collectableTexture);
    }

    // Elegir una celda libre cerca del centro como goal
    if (!emptyCells.empty()) {
        // Ordenar por cercanía al centro
        sf::Vector2f center(cols * cellSize.x / 2.f, rows * cellSize.y / 2.f);

        std::sort(emptyCells.begin(), emptyCells.end(),
            [center](const sf::Vector2f& a, const sf::Vector2f& b) {
                float da = std::hypot(a.x - center.x, a.y - center.y);
                float db = std::hypot(b.x - center.x, b.y - center.y);
                return da < db;
            });

        // Primera celda cercana al centro
        sf::Vector2f goalPos = emptyCells.front();

        goal.emplace(
            sf::Vector2f(cellSize.x * 0.8f, cellSize.y * 0.8f),
            goalPos,
            *goalClosedTexture,
            *goalOpenTexture
        );
    }

    
    addBorderWalls(cols * cellSize.x, rows * cellSize.y, BORDER_THICKNESS);
}

void Labyrinth::generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize)
{
    grid = layout;
    walls.clear();
    floors.clear();

    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            sf::Vector2f pos(
                col * cellSize.x + cellSize.x / 2.f,
                row * cellSize.y + cellSize.y / 2.f
            );

            sf::Vector2f size(cellSize.x, cellSize.y);

            switch (grid[row][col]) {
            case CellType::Wall: {
                walls.emplace_back(size, pos, *wallTexture);
                break;
            }
            case CellType::Goal: {
                // TODO: 
                break;
            }
            case CellType::Empty: {
                floors.emplace_back(size, pos, *floorTexture);
                break;
            }
            default:
                break;
            }
        }
    }
}

void Labyrinth::addBorderWalls(float width, float height, float thickness)
{
    // TOP
    walls.emplace_back(
        sf::Vector2f(width, thickness),              // width = whole level, altitude = thickness
        sf::Vector2f(width / 2.f, thickness / 2.f), *borderTexture
    );

    // BOTTOM
    walls.emplace_back(
        sf::Vector2f(width, thickness),
        sf::Vector2f(width / 2.f, height - thickness / 2.f), *borderTexture
    );

    // LEFT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(thickness / 2.f, height / 2.f), *borderTexture
    );

    // RIGHT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(width - thickness / 2.f, height / 2.f), *borderTexture
    );
}

void Labyrinth::loadTextures()
{
    borderTexture = &ResourceManager::getInstance().getTexture("tiles/border.png");

    wallTexture = &ResourceManager::getInstance().getTexture("tiles/wall.png");

    floorTexture = &ResourceManager::getInstance().getTexture("tiles/floor.png");

    collectableTexture = &ResourceManager::getInstance().getTexture("items/collectable.png");

    goalClosedTexture = &ResourceManager::getInstance().getTexture("items/chest_empty_0.png");
    goalOpenTexture = &ResourceManager::getInstance().getTexture("items/chest_full_open.png");
}