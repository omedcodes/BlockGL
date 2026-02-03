/**
* AudioManager.cpp isnt in Use anymore if you do want to work with sounds in this BlockGL then
* Consider uncommenting this file and implement the following functions into the Voxel Engine.
*/

/*
#include "AudioManager.h"

AudioManager* AudioManager::instancePtr = nullptr;

AudioManager::~AudioManager() {
    for (auto src : sources) alDeleteSources(1, &src);
    for (auto buf : buffers) alDeleteBuffers(1, &buf);

    alcMakeContextCurrent(nullptr);
    if (context) alcDestroyContext(context);
    if (device) alcCloseDevice(device);
}

bool AudioManager::init() {
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open OpenAL device\n";
        return false;
    }

    context = alcCreateContext(device, nullptr);
    if (!context) {
        std::cerr << "Failed to create OpenAL context\n";
        return false;
    }

    alcMakeContextCurrent(context);
    return true;
}

ALuint AudioManager::loadAudioFile(const std::string& filePath) {
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(filePath.c_str(), SFM_READ, &sfInfo);
    if (!sndFile) {
        std::cerr << "Failed to open audio file: " << filePath << "\n";
        return 0;
    }

    std::vector<short> samples(sfInfo.frames * sfInfo.channels);
    sf_read_short(sndFile, samples.data(), samples.size());
    sf_close(sndFile);

    ALenum format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, samples.data(), static_cast<ALsizei>(samples.size() * sizeof(short)), sfInfo.samplerate);
    buffers.push_back(buffer);
    return buffer;
}

void AudioManager::playMusic(const std::string& filePath) {
    ALuint buffer = loadAudioFile(filePath);
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcePlay(source);
    sources.push_back(source);
}

void AudioManager::playSound(const std::string& filePath) {
    ALuint buffer = loadAudioFile(filePath);
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    sources.push_back(source);
}
*/