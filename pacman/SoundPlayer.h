#pragma once
#include <memory>
#include "Events.h"

namespace dae
{
	class SoundPlayer : public Observer, std::enable_shared_from_this<SoundPlayer>
    {
	public:
		static std::shared_ptr<SoundPlayer>Create();
		void HandleEvent(const Event& event) override;

	private:
		SoundPlayer() = default;
    };
}
