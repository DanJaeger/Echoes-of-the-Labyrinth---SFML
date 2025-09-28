#include "AudioManager.h"
#include <iostream>
#include <algorithm>

// Singleton instance
AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

// Load a sound effect and store it in memory
void AudioManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        logError("Failed to load sound", filePath);
        return;
    }
    soundBuffers[name] = std::move(buffer);
}

// Play a sound effect by name
void AudioManager::playSound(const std::string& name, float volume) {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        logError("Sound not loaded: " + name);
        return;
    }

    auto sound = std::make_shared<sf::Sound>();
    sound->setBuffer(it->second);

    // Apply per-sound volume scaled by global SFX volume
    sound->setVolume(volume * (sfxVolume / Config::Audio::SFX_VOLUME));
    sound->play();

    activeSounds.push_back(sound);
}

// Play background music from a file
void AudioManager::playMusic(const std::string& filePath, bool loop, float volume) {
    if (!music.openFromFile(filePath)) {
        logError("Failed to load music", filePath);
        return;
    }
    music.setLoop(loop);
    music.setVolume(volume);
    music.play();
}

// Stop music
void AudioManager::stopMusic() {
    music.stop();
}

// Pause music
void AudioManager::pauseMusic() {
    music.pause();
}

// Resume music
void AudioManager::resumeMusic() {
    music.play();
}

// Set background music volume
void AudioManager::setMusicVolume(float volume) {
    music.setVolume(volume);
}

// Set global sound effects volume
void AudioManager::setSfxVolume(float volume) {
    sfxVolume = volume;
}

// Remove finished sounds from the active list
void AudioManager::update() {
    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(),
            [](const std::shared_ptr<sf::Sound>& s) {
                return s->getStatus() == sf::Sound::Stopped;
            }),
        activeSounds.end()
    );
}

// Helper method to log errors
void AudioManager::logError(const std::string& message, const std::string& filePath) {
    if (!filePath.empty())
        std::cerr << "AudioManager Error: " << message << " (" << filePath << ")" << std::endl;
    else
        std::cerr << "AudioManager Error: " << message << std::endl;
}
