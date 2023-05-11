#pragma once
#include <iostream>
#include <mutex>
#include <queue>


using Sound_id = unsigned short;
struct PlayRequest
{
	int id{};
	float volume{};
};
class SoundSystem
{
public:
	SoundSystem()
	{
		
	};
	virtual ~SoundSystem() =default;
	virtual void InitializeSoundSystem(){} ;
	virtual void Play(const Sound_id /*id*/, const float /*volume*/) {};
	virtual void RegisterSound(const Sound_id /*id*/, const std::string& /*path*/) {};

	
};

class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();
	virtual ~SDLSoundSystem();

	void InitializeSoundSystem() override;
	void RegisterSound(const Sound_id id, const std::string& fileName) override;
	void Play(const Sound_id id, const float volume) override;

private:
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* pImpl;
};

class logging_sound_system final : public SoundSystem
{
	std::shared_ptr<SoundSystem> _real_ss;
public:
	logging_sound_system(std::shared_ptr<SoundSystem> ss) : _real_ss{ ss } {}
	virtual ~logging_sound_system() {};

	void InitializeSoundSystem() override
	{
		_real_ss->InitializeSoundSystem();
		std::cout << "Initializing sound system" << std::endl;
	}
	void RegisterSound(const Sound_id id, const std::string& path) override {
		_real_ss->RegisterSound(id, path);
		std::cout << "registering sound with name: " << path << " and id: " << id << std::endl;
	}
	void Play(const Sound_id id, const float volume) override {
		_real_ss->Play(id, volume);
		std::cout << "playing " << id << " at volume " << volume << std::endl;
	}
};

class NullSoundSystem final : public SoundSystem
{
	void InitializeSoundSystem() override {}
	void Play(const Sound_id, const float) override {}
	void RegisterSound(const Sound_id, const std::string&) override {}
};

class ServiceLocator final
{
public:
	ServiceLocator() { ss_Instance = std::make_shared<NullSoundSystem>(); }

	static SoundSystem& GetSoundSystem() { return *ss_Instance.get(); }
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
	{
		if (ss != nullptr)
		{
			ss_Instance = ss;
		}
	}
	static void Shutdown() {
		if (ss_Instance != std::make_shared<SoundSystem>(default_ss))
		{
			ss_Instance = nullptr;
		}
		ss_Instance = std::make_shared<SoundSystem>(default_ss);
	}

private:
	static std::shared_ptr<SoundSystem> ss_Instance;
	static NullSoundSystem default_ss;
};
