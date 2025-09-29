#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "Config.h"

/**
 * @class ResourceManager
 * @brief Singleton responsible for loading and managing textures and fonts.
 *
 * - Prevents redundant loading of the same file.
 * - Stores resources in memory for reuse.
 * - Provides centralized access across the game.
 */
class ResourceManager {
public:
    // ---------------- Singleton restrictions ----------------
    ResourceManager(const ResourceManager&) = delete;            ///< Disable copy
    ResourceManager& operator=(const ResourceManager&) = delete; ///< Disable assignment

    /**
     * @brief Access the global instance of the ResourceManager.
     * @return ResourceManager& Reference to the singleton instance.
     */
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    // ---------------- Texture Management ----------------
    /**
     * @brief Retrieves a texture from memory or loads it if not already present.
     * @param filename Name of the texture file (relative to textureBasePath).
     * @return sf::Texture& Reference to the loaded texture.
     */
    sf::Texture& getTexture(const std::string& filename) {
        // Check if already loaded
        auto it = textures.find(filename);
        if (it != textures.end()) {
            return *it->second;
        }

        // Load new texture if missing
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(textureBasePath + filename)) {
            std::cerr << "[ResourceManager] Error loading texture: "
                << textureBasePath + filename << std::endl;
        }

        // Apply smoothing (bilinear filtering)
        texture->setSmooth(true);

        // Store and return reference
        sf::Texture& ref = *texture;
        textures[filename] = std::move(texture);
        return ref;
    }

    // ---------------- Font Management ----------------
    /**
     * @brief Retrieves a font from memory or loads it if not already present.
     * @param filename Name of the font file (relative to fontBasePath).
     * @return sf::Font& Reference to the loaded font.
     */
    sf::Font& getFont(const std::string& filename) {
        // Check if already loaded
        auto it = fonts.find(filename);
        if (it != fonts.end()) {
            return *it->second;
        }

        // Load new font if missing
        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(fontBasePath + filename)) {
            std::cerr << "[ResourceManager] Error loading font: "
                << fontBasePath + filename << std::endl;
        }

        // Store and return reference
        sf::Font& ref = *font;
        fonts[filename] = std::move(font);
        return ref;
    }

    // ---------------- Path Configuration ----------------
    void setTextureBasePath(const std::string& path) { textureBasePath = path; }
    void setFontBasePath(const std::string& path) { fontBasePath = path; }

private:
    /**
     * @brief Private constructor initializes default base paths from Config.
     */
    ResourceManager()
        : textureBasePath(Config::Resources::TEXTURE_PATH),
        fontBasePath(Config::Resources::FONT_PATH) {
    }

    // ---------------- Data Members ----------------
    std::string textureBasePath; ///< Base directory for textures
    std::string fontBasePath;    ///< Base directory for fonts

    std::map<std::string, std::unique_ptr<sf::Texture>> textures; ///< Loaded textures
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;       ///< Loaded fonts
};
