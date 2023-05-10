#include "SoundSystem.h"

#include <SDL_error.h>

#include "SDL_mixer.h"
#include <vector>

#include "AudioClip.h"

std::shared_ptr<SoundSystem> ServiceLocator::ss_Instance = std::make_shared<NullSoundSystem>(default_ss);
NullSoundSystem ServiceLocator::default_ss;

class SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl() = default;
	virtual ~SDLSoundSystemImpl();

	void InitializeSoundSystem();
	void RegisterSound(const Sound_id id, const std::string& fileName);
	void Play(const Sound_id id, const float volume);

private:
	size_t m_MaxClips{ 50 };
	std::vector<std::shared_ptr<AudioClip>> m_pAudioclips{};
};



//SDLSoundSystem implementation
SDLSoundSystem::SDLSoundSystem()
{
	pImpl = new SDLSoundSystemImpl();
}

SDLSoundSystem::~SDLSoundSystem()
{
	delete pImpl;
}

void SDLSoundSystem::InitializeSoundSystem()
{
	pImpl->InitializeSoundSystem();
}

void SDLSoundSystem::RegisterSound(const Sound_id id, const std::string& fileName)
{
	pImpl->RegisterSound(id, fileName);
}

void SDLSoundSystem::Play(const Sound_id id, const float volume)
{
	pImpl->Play(id, volume);
}

//SDLSoundSystemIMPL implementation
SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	Mix_CloseAudio();
}

void SDLSoundSystem::SDLSoundSystemImpl::InitializeSoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	m_pAudioclips.resize(m_MaxClips);
}

void SDLSoundSystem::SDLSoundSystemImpl::RegisterSound(const Sound_id id, const std::string& fileName)
{

	m_pAudioclips[id] = std::make_shared<AudioClip>(fileName);
}

void SDLSoundSystem::SDLSoundSystemImpl::Play(const Sound_id id, const float volume)
{
	if (id > m_pAudioclips.size())
		return;

	auto audioclip = m_pAudioclips[id];
	if (!audioclip->IsLoaded())
		audioclip->LoadSound();
	audioclip->SetVolume((int)(volume * 100));
	audioclip->PlaySound();
}

//#include "SoundSystem.h"
//
//#include <vector>
//
//
//std::shared_ptr<BaseSoundSystem> ServiceLocator::ss_Instance = std::make_shared<NullSoundSystem>(ss_Default);
//NullSoundSystem ServiceLocator::ss_Default;
//
//class SDLSoundSystem::SDLSoundSystemImpl
//{
//public:
//	SDLSoundSystemImpl() = default;
//	virtual ~SDLSoundSystemImpl();
//
//	void InitializeSoundSystem();
//	void RegisterSound(const Sound_id id, const std::string& fileName);
//	void PlaySound(const Sound_id id, const float volume);
//
//private:
//	size_t m_MaxClips{ 50 };
//	std::vector<std::shared_ptr<AudioClip>> m_pAudioclips;
//};
//
//
//
////SDLSoundSystem implementation
//SDLSoundSystem::SDLSoundSystem()
//{
//	pImpl = new SDLSoundSystemImpl();
//}
//
//SDLSoundSystem::~SDLSoundSystem()
//{
//	delete pImpl;
//}
//
//void SDLSoundSystem::InitializeSoundSystem()
//{
//	pImpl->InitializeSoundSystem();
//}
//
//void SDLSoundSystem::RegisterSound(const Sound_id id, const std::string& fileName)
//{
//	pImpl->RegisterSound(id, fileName);
//}
//
//void SDLSoundSystem::PlaySound(const Sound_id id, const float volume)
//{
//	pImpl->PlaySound(id, volume);
//}
//
////SDLSoundSystemIMPL implementation
//SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
//{
//	Mix_CloseAudio();
//}
//
//void SDLSoundSystem::SDLSoundSystemImpl::InitializeSoundSystem()
//{
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
//	{
//		printf("Mix_OpenAudio: %s\n", Mix_GetError());
//		exit(2);
//	}
//
//	m_pAudioclips.resize(m_MaxClips);
//}
//
//void SDLSoundSystem::SDLSoundSystemImpl::RegisterSound(const Sound_id id, const std::string& fileName)
//{
//
//	m_pAudioclips[id] = std::make_shared<AudioClip>(fileName);
//}
//
//void SDLSoundSystem::SDLSoundSystemImpl::PlaySound(const Sound_id id, const float volume)
//{
//	if (id > m_pAudioclips.size())
//		return;
//
//	auto audioclip = m_pAudioclips[id];
//	if (!audioclip->IsLoaded())
//		audioclip->LoadSound();
//	audioclip->SetVolume((int)(volume * 100));
//	audioclip->PlaySound();
//}