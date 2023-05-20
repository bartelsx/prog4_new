#pragma once
#include "SoundSystem.h"

namespace dae
{

	class ServiceLocator final
	{
	public:

		static SoundSystem& GetSoundSystem()
		{
			if (ss_Instance == nullptr)
			{
				ss_Instance = std::make_shared<NullSoundSystem>();
			}
			return *ss_Instance.get();
		}

		static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
		{
			if (ss != nullptr)
			{
				ss_Instance = ss;
			}
		}

		static void Shutdown()
		{
			ss_Instance = nullptr;
		}

	private:
		static std::shared_ptr<SoundSystem> ss_Instance;
	};
}
