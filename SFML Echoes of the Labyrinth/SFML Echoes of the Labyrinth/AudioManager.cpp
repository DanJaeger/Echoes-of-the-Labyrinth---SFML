#include "AudioManager.h"
#include <iostream>
#include <algorithm>

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error: no se pudo cargar el sonido " << filePath << std::endl;
        return;
    }
    soundBuffers[name] = std::move(buffer);
}

void AudioManager::playSound(const std::string& name, float volume) {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        std::cerr << "Error: sonido '" << name << "' no cargado." << std::endl;
        return;
    }

    auto sound = std::make_shared<sf::Sound>();
    sound->setBuffer(it->second);
    sound->setVolume(volume * (sfxVolume / 100.f));
    sound->play();

    activeSounds.push_back(sound);
}

void AudioManager::playMusic(const std::string& filePath, bool loop, float volume) {
    if (!music.openFromFile(filePath)) {
        std::cerr << "Error: no se pudo cargar la música " << filePath << std::endl;
        return;
    }
    music.setLoop(loop);
    music.setVolume(volume);
    music.play();
}

void AudioManager::stopMusic() {
    music.stop();
}

void AudioManager::pauseMusic() {
    music.pause();
}

void AudioManager::resumeMusic() {
    music.play();
}

void AudioManager::setMusicVolume(float volume) {
    music.setVolume(volume);
}

void AudioManager::setSfxVolume(float volume) {
    sfxVolume = volume;
}

void AudioManager::update() {
    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(),
            [](const std::shared_ptr<sf::Sound>& s) { return s->getStatus() == sf::Sound::Stopped; }),
        activeSounds.end()
    );
}
