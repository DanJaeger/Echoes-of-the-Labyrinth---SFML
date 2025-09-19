#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Animation {
public:
    Animation(float switchTime = 0.15f, bool loop = true)
        : textureBasePath("assets/textures/"), switchTime(switchTime), totalTime(0.f), currentFrame(0), loop(loop), finished(false) {
    }

    void addFrame(const std::string& texturePath) {
        sf::Texture tex;
        if (!tex.loadFromFile(textureBasePath + texturePath))
            throw std::runtime_error("No se pudo cargar " + texturePath);
        textures.push_back(std::move(tex));
    }

    void update(float dt) {
        if (textures.empty()) return;

        totalTime += dt;
        if (totalTime >= switchTime) {
            totalTime -= switchTime;
            currentFrame++;

            if (currentFrame >= textures.size()) {
                if (loop) {
                    currentFrame = 0;
                }
                else {
                    currentFrame = textures.size() - 1;
                    finished = true;
                }
            }
        }
    }

    const sf::Texture& getCurrentTexture() const {
        return textures[currentFrame];
    }

    void reset() {
        currentFrame = 0;
        totalTime = 0.f;
        finished = false;
    }

    bool isFinished() const {
        return finished;
    }

private:
    std::string textureBasePath;

    std::vector<sf::Texture> textures;
    float switchTime;
    float totalTime;
    size_t currentFrame;

    bool loop;
    bool finished;
};
