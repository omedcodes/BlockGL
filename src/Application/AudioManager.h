#pragma once

#include "../BlockGL.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <string>
#include <vector>

class AudioManager {
    static AudioManager *instancePtr;

    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

    std::vector<ALuint> buffers;
    std::vector<ALuint> sources;
    
    ALuint loadAudioFile(const std::string& filePath);

    AudioManager() = default;
    ~AudioManager();

public:
    static AudioManager &instane() {
        if (!instancePtr) instancePtr = new AudioManager();
        return *instancePtr;
    }

    bool init();

    void playMusic(const std::string& filePath);
    void playSound(const std::string& filePath);

    AudioManager(const AudioManager &) = delete;
    AudioManager(AudioManager &&) noexcept = delete;
    AudioManager &operator=(const AudioManager &) = delete;
    AudioManager &operator=(AudioManager &&) noexcept = delete;
};