#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>

class ResourceManager {
public:
    // Stop multiple copies
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

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
        if (!texture->loadFromFile(basePath + filename)) {
            std::cerr << "? Error loading texture: " << filename << std::endl;
        }
        texture->setSmooth(true); // smoothing texture

        sf::Texture& ref = *texture;
        textures[filename] = std::move(texture);
        return ref;
    }

    // change the base folder for textures to assets/textures/
    void setBasePath(const std::string& path) {
        basePath = path;
    }

private:
    ResourceManager() : basePath("assets/textures/") {}

    std::string basePath;
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
};

