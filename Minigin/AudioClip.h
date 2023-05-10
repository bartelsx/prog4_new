#pragma once
#include <string>

#include "SDL_mixer.h"


class AudioClip
{
public:
    AudioClip(const std::string& fileName);
    ~AudioClip();

    AudioClip(const AudioClip&) = delete;
    AudioClip(AudioClip&&) = delete;
    AudioClip& operator= (const AudioClip&) = delete;
    AudioClip& operator= (const AudioClip&&) = delete;

    void LoadSound();
    void PlaySound();
    void SetVolume(int volume);

    bool IsLoaded() const;

private:
    std::string m_SoundName{};
    Mix_Chunk* m_pSound{ nullptr };
    bool m_IsLoaded{ false };
};

