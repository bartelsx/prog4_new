#pragma once
#include <memory>
#include "Observer.h"

namespace dae
{
	class SoundPlayer : public Observer, std::enable_shared_from_this<SoundPlayer>
    {
	public:
		static std::shared_ptr<SoundPlayer>Create();
		void Notify(Event& event) override;

	private:
		SoundPlayer() = default;
    };
}
