#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class AudioManager {
public:
    static AudioManager& getInstance();

    void loadSound(const std::string& name, const std::string& filePath);
    void playSound(const std::string& name, float volume = 100.f);

    void playMusic(const std::string& filePath, bool loop = true, float volume = 100.f);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    void update();
    void setMusicVolume(float volume);
    void setSfxVolume(float volume);

private:
    AudioManager() = default;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::vector<std::shared_ptr<sf::Sound>> activeSounds;

    sf::Music music;
    float sfxVolume = 100.f;
};
