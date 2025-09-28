#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random> 
#include <optional>
#include <functional>
#include "Walls.h"
#include "Player.h"
#include "Floor.h"
#include "Collectable.h"
#include "Goal.h"

// Tipos de celda posibles en la grilla del laberinto
enum class CellType {
    Empty,  // Espacio vacío por donde el jugador puede caminar
    Wall,   // Pared que bloquea el paso
    Goal    // Objetivo (puerta/cofre de salida)
};

class Labyrinth {
public:
    Labyrinth();

    // Actualiza la lógica del laberinto (colisiones, animaciones de objetos, etc.)
    void update(float dt, Player& player);

    // Dibuja todos los elementos del laberinto en la ventana
    void draw(sf::RenderWindow& window);

    // Verifica y maneja las colisiones del jugador con paredes, ítems y meta
    void handleCollisions(Player& player);

    // Genera un nuevo laberinto en base al tamaño de la ventana y tamaño de celdas
    void generate(sf::Vector2u windowSize, unsigned cellPixelSize = 32);

    // Reinicia el laberinto con una nueva disposición
    void reset(sf::Vector2u windowSize);

    // Cantidad total de coleccionables que deben recogerse
    int getCollectablesCount() const;

    // Cantidad de coleccionables recogidos hasta ahora
    int getCollectedCount() const;

    // Devuelve el punto de aparición inicial del jugador
    sf::Vector2f getSpawnPoint() const;

    // Establece un callback que se ejecuta cuando el jugador gana
    void setOnWin(std::function<void()> callback);

private:
    // Agrega muros que rodean los bordes del laberinto
    void addBorderWalls(float width, float height, float thickness);

    // Genera paredes, pisos y meta a partir de una grilla
    void generateFromGrid(const std::vector<std::vector<CellType>>& layout, sf::Vector2f cellSize);

    // Algoritmo DFS para generar un laberinto de manera procedural
    void generateMazeDFS(size_t rows, size_t cols, sf::Vector2f cellSize);

    // Carga las texturas necesarias para los elementos
    void loadTextures();

    // Recursos gráficos
    const sf::Texture* backgroundTexture;
    sf::Sprite backgroundSprite;

    const sf::Texture* borderTexture;
    const sf::Texture* wallTexture;
    const sf::Texture* floorTexture;
    const sf::Texture* collectableTexture;
    const sf::Texture* goalClosedTexture;
    const sf::Texture* goalOpenTexture;

    // Elementos del laberinto
    std::vector<Walls> walls;
    std::vector<Floor> floors;
    std::vector<Collectable> collectables;
    std::optional<Goal> goal;

    // Representación del laberinto como grilla de celdas
    std::vector<std::vector<CellType>> grid;

    // Generador aleatorio para distribución procedural
    std::mt19937 rng;

    // Dimensiones del laberinto
    size_t rows;
    size_t cols;
    sf::Vector2f cellSize;

    // Sistema de coleccionables
    int numberOfCollectables = Config::Labyrinth::NUMBER_OF_COLLECTABLES;
    int collectedKeys = 0;

    // Callback cuando el jugador gana
    std::function<void()> onWin;
};

#endif
