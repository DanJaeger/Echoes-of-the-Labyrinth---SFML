#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>

class ResourceManager {
public:
    // Stop multiple copies
    ResourceManager(const ResourceManager&) = delete; //doesn't allow to copy
    ResourceManager& operator=(const ResourceManager&) = delete; //doesn't allow to assign

    // Singleton
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    sf::Texture& getTexture(const std::string& filename) {
        auto it = textures.find(filename);
        if (it != textures.end()) {
            return *it->second;
        }

        // Load texture if it doesn't exist
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(textureBasePath + filename)) {
            std::cerr << "? Error loading texture: " << filename << std::endl;
        }
        texture->setSmooth(true); // bilinear filtering

        sf::Texture& ref = *texture;
        textures[filename] = std::move(texture);
        return ref;
    }

    sf::Font& getFont(const std::string& filename) {
        auto it = fonts.find(filename);
        if (it != fonts.end()) {
            return *it->second;
        }

        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(fontBasePath + filename)) {
            std::cerr << "[ResourceManager] Error loading font: "
                << fontBasePath + filename << std::endl;
        }

        sf::Font& ref = *font;
        fonts[filename] = std::move(font);
        return ref;
    }


    void setTextureBasePath(const std::string& path) { textureBasePath = path; }
    void setFontBasePath(const std::string& path) { fontBasePath = path; }

private:
    ResourceManager()
        : textureBasePath("assets/textures/"), fontBasePath("assets/fonts/") {
    }

    std::string textureBasePath;
    std::string fontBasePath;

    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;
};

