#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "Config.h"

/**
 * @brief Manages sound effects and background music for the game.
 * Implements a Singleton pattern so it can be accessed globally.
 */

class AudioManager {
public:
    /// Get the single instance of the AudioManager
    static AudioManager& getInstance();

    /// Load a sound effect into memory
    void loadSound(const std::string& name, const std::string& filePath);

    /// Play a loaded sound effect
    void playSound(const std::string& name, float volume = Config::Audio::SFX_VOLUME);

    /// Play background music
    void playMusic(const std::string& filePath, bool loop = true, float volume = Config::Audio::MUSIC_VOLUME);

    /// Stop background music immediately
    void stopMusic();

    /// Pause currently playing music
    void pauseMusic();

    /// Resume paused music
    void resumeMusic();

    /// Remove stopped sound effects from memory
    void update();

    /// Set global music volume (0 - 100)
    void setMusicVolume(float volume);

    /// Set global sound effect volume (0 - 100)
    void setSfxVolume(float volume);

private:
    //Singleton
    AudioManager() = default;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    /// Helper method to print loading/playing errors
    void logError(const std::string& message, const std::string& filePath = "");

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;   // Loaded sound buffers
    std::vector<std::shared_ptr<sf::Sound>> activeSounds;            // Active sounds currently playing
    sf::Music music;                                                 // Background music
    float sfxVolume = Config::Audio::SFX_VOLUME;                     // Global sound effects volume
};
