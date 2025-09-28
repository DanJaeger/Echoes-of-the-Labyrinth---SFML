#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include "Config.h"

/**
 * @class Animation
 * @brief Handles frame-based animations using SFML textures.
 *
 * - Loads frames (textures) from files.
 * - Cycles through them over time according to a switch interval.
 * - Supports looping or one-shot animations.
 */
class Animation {
public:
    /**
     * @brief Construct a new Animation.
     * @param switchTime Time in seconds before switching to the next frame.
     * @param loop Whether the animation should loop back to the start.
     */
    Animation(float switchTime = Config::Animation::SWITCH_TIME, bool loop = true)
        : textureBasePath(Config::Animation::DEFAULT_TEXTURE_PATH),
        switchTime(switchTime),
        totalTime(0.f),
        currentFrame(0),
        loop(loop),
        finished(false) {
    }

    /**
     * @brief Adds a frame to the animation.
     * @param texturePath Path to the frame texture (relative to textureBasePath).
     * @throws std::runtime_error if the texture cannot be loaded.
     */
    void addFrame(const std::string& texturePath) {
        sf::Texture tex;
        if (!tex.loadFromFile(textureBasePath + texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        textures.push_back(std::move(tex));
    }

    /**
     * @brief Updates the animation based on elapsed time.
     * @param dt Delta time (seconds since last frame).
     */
    void update(float dt) {
        if (textures.empty()) return;

        totalTime += dt;
        if (totalTime >= switchTime) {
            totalTime -= switchTime;
            currentFrame++;

            // Handle looping or one-shot completion
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

    /**
     * @brief Retrieves the current frame's texture.
     * @return const sf::Texture& Reference to the current texture.
     */
    const sf::Texture& getCurrentTexture() const {
        return textures[currentFrame];
    }

    /**
     * @brief Resets the animation to its initial state.
     */
    void reset() {
        currentFrame = 0;
        totalTime = 0.f;
        finished = false;
    }

    /**
     * @brief Checks if a non-looping animation has finished playing.
     * @return true if finished, false otherwise.
     */
    bool isFinished() const {
        return finished;
    }

private:
    // ---------------- Data Members ----------------
    std::string textureBasePath; ///< Base path for loading textures
    std::vector<sf::Texture> textures; ///< Frames of the animation

    float switchTime;   ///< Time between frames
    float totalTime;    ///< Accumulated time
    size_t currentFrame;///< Index of the current frame

    bool loop;     ///< Whether animation loops
    bool finished; ///< True if non-looping animation reached the end
};
