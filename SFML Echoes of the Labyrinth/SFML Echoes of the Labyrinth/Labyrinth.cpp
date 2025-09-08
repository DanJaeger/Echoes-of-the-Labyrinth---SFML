#include "Labyrinth.h"
#include "ResourceManager.h"
#include <iostream>
#include <stack>
#include <random>

Labyrinth::Labyrinth(const std::string& textureFile, const sf::Vector2u& windowSize) {
    texture = ResourceManager::getInstance().getTexture(textureFile);
    sprite.setTexture(texture);

    // Fixes background texture size
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    // Center texture
    sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void Labyrinth::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    for (auto& wall : walls)
        wall.draw(window);
}

void Labyrinth::handleCollisions(Player& player)
{
    for (auto& wall : walls) {
        player.getCollider().checkCollision(wall.getCollider(), 0.0f);
    }
}

void Labyrinth::addBorderWalls(float width, float height, float thickness)
{
    // TOP
    walls.emplace_back(
        sf::Vector2f(width, thickness),              // width = whole level, altitude = thickness
        sf::Vector2f(width / 2.f, thickness / 2.f) 
    );

    // BOTTOM
    walls.emplace_back(
        sf::Vector2f(width, thickness),
        sf::Vector2f(width / 2.f, height - thickness / 2.f)
    );

    // LEFT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(thickness / 2.f, height / 2.f)
    );

    // RIGHT
    walls.emplace_back(
        sf::Vector2f(thickness, height),
        sf::Vector2f(width - thickness / 2.f, height / 2.f)
    );
}

void Labyrinth::generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize)
{
    grid = layout;
    walls.clear();

    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            sf::Vector2f pos(
                col * cellSize.x + cellSize.x / 2.f,
                row * cellSize.y + cellSize.y / 2.f
            );

            switch (grid[row][col]) {
            case CellType::Wall: {
                sf::Vector2f size(cellSize.x, cellSize.y);
                walls.emplace_back(size, pos);
                break;
            }
            case CellType::Goal: {
                // TODO: 
                break;
            }
            default:
                break;
            }
        }
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

    // 4. Define goal (On the oposite corner)
    grid[rows - 1][cols - 1] = CellType::Goal;

    // 5. Converting grid into walls
    generateFromGrid(grid, cellSize);

    // 6. 
    addBorderWalls(cols * cellSize.x, rows * cellSize.y, BORDER_THICKNESS);
}

