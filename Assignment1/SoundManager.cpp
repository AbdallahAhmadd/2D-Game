//
//  SoundManager.cpp
//  Assignment1
//
//  Created by NANNA on 18/10/2024.
//

#include "SoundManager.hpp"
#include <map>
#include <iostream>

std::map<std::string, sf::SoundBuffer> soundBuffers;
std::map<std::string, sf::Sound> sounds;

void loadSounds() {
    // List of sound files to load
    std::map<std::string, std::string> soundFiles = {
        {"collect", "/Users/Abdallah/Documents/Semester 7🤞/Computer Graphics/Labs i Solve/Assignment1/Assignment1/Sounds/CollectSound.wav"},
        {"Gameover", "/Users/Abdallah/Documents/Semester 7🤞/Computer Graphics/Labs i Solve/Assignment1/Assignment1/Sounds/GameOver.wav"},
        {"Gamewin", "/Users/Abdallah/Documents/Semester 7🤞/Computer Graphics/Labs i Solve/Assignment1/Assignment1/Sounds/GameWin.wav"},
        {"hit","/Users/Abdallah/Documents/Semester 7🤞/Computer Graphics/Labs i Solve/Assignment1/Assignment1/Sounds/ObstacleHit.wav"},
        {"main","/Users/Abdallah/Documents/Semester 7🤞/Computer Graphics/Labs i Solve/Assignment1/Assignment1/Sounds/GameMusic.wav"}
       
    };

    for (const auto& [name, path] : soundFiles) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) {
            std::cerr << "Failed to load sound file: " << path << std::endl;
        } else {
            soundBuffers[name] = buffer;
            sf::Sound sound;
            sound.setBuffer(soundBuffers[name]);
            sounds[name] = sound;
        }
    }
}

void playSound(const std::string& soundName) {
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        if (soundName == "main") {
            it->second.setVolume(15);
            it->second.setLoop(true);
        }
        else{
            it->second.setVolume(100);
        }
        it->second.play();
    }
}
