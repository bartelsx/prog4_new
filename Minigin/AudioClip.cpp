#include "AudioClip.h"
#include <stdio.h>
#include <sstream>
#include "SDL_mixer.h"

AudioClip::AudioClip(const std::string& fileName)
	:m_SoundName{ fileName }
{
}

AudioClip::~AudioClip()
{
	Mix_FreeChunk(m_pSound);
}

void AudioClip::LoadSound()
{
	m_pSound = Mix_LoadWAV(m_SoundName.c_str());
	if (!m_pSound)
		printf("Mix_LoadWav: %s\n", Mix_GetError());
	else
		m_IsLoaded = true;
}

void AudioClip::PlaySound()
{
	if (m_IsLoaded)
		Mix_PlayChannel(-1, m_pSound, 0);
}

void AudioClip::SetVolume(int volume)
{
	m_pSound->volume = static_cast<Uint8>(volume);
}

bool AudioClip::IsLoaded() const
{
	return m_IsLoaded;
}
