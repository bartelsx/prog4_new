#include "SoundSystem.h"

#include <SDL_error.h>

#include "SDL_mixer.h"
#include <vector>

#include "AudioClip.h"

using namespace dae;

class SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl();
	virtual ~SDLSoundSystemImpl();

	void InitializeSoundSystem();
	void Update();
	void RegisterSound(const Sound_id id, const std::string& fileName);
	void Play(const Sound_id id, const float volume);

private:
	size_t m_MaxClips{ 50 };
	std::vector<std::shared_ptr<AudioClip>> m_pAudioclips{};
	std::jthread m_thread;
	std::mutex m_mt;
	std::condition_variable m_cv;
	std::queue<PlayRequest> m_playRequests{};
	bool m_ready{ false };
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
SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
{
	m_thread = std::jthread([this] { this->Update(); });
}
SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	Mix_CloseAudio();
	m_ready = true;
	m_cv.notify_all();
	
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
void SDLSoundSystem::SDLSoundSystemImpl::Update()
{
	while (!m_ready)
	{
		std::unique_lock<std::mutex> lck(m_mt);

		m_cv.wait(lck, [&]() {return m_playRequests.size() > 0 || m_ready; });
		if (m_ready)
		{
			break;
		}
		auto request = m_playRequests.front();
		m_playRequests.pop();
		int id = request.id;
		auto audioclip = m_pAudioclips[id];
		lck.unlock();
		
		float volume = request.volume;
		if (!audioclip->IsLoaded())
			audioclip->LoadSound();
		audioclip->SetVolume((int)(volume * 100));
		audioclip->PlaySound();
	}
}
void SDLSoundSystem::SDLSoundSystemImpl::RegisterSound(const Sound_id id, const std::string& fileName)
{

	m_pAudioclips[id] = std::make_shared<AudioClip>(fileName);
}

void SDLSoundSystem::SDLSoundSystemImpl::Play(const Sound_id id, const float volume)
{
	if (id > m_pAudioclips.size())
		return;


	m_playRequests.push(PlayRequest{ id,volume });
	m_cv.notify_one();
}
