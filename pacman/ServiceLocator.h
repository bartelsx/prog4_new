#pragma once
#include "SoundSystem.h"

namespace dae
{
	static std::shared_ptr<SoundSystem>  ss_Instance = std::make_shared<NullSoundSystem>();

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem()
		{
			return *ss_Instance;
		}

		static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
		{
			ss_Instance = ss;
		}
	};

}
