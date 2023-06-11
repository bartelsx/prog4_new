#pragma once
#include <memory>
#include "Events.h"
#include "SoundSystem.h"

namespace dae
{
	class SoundPlayer : public Observer, std::enable_shared_from_this<SoundPlayer>
    {
	public:
		static std::shared_ptr<SoundPlayer>Create();
		void HandleEvent(const Event& event) override;
		void SetMuted(bool muted);
		bool GetMuted() const;
		void ToggleMuted();

	private:
		SoundPlayer() = default;
		void Play(const Sound_id id, const float volumne );

		bool m_Muted{};
    };
}
