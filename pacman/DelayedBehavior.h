#pragma once
#include "GhostMoveBehavior.h"

namespace dae
{
	class DelayedBehavior : public GhostMoveBehavior, public Observer
	{
	public:
		~DelayedBehavior() override = default;
		DelayedBehavior(const DelayedBehavior& other) = delete;
		DelayedBehavior(DelayedBehavior&& other) = delete;
		DelayedBehavior& operator=(const DelayedBehavior& other) = delete;
		DelayedBehavior& operator=(DelayedBehavior&& other) = delete;

		static std::shared_ptr<DelayedBehavior> Create(float delay, const std::shared_ptr<GhostMoveBehavior>& baseBehavior)
		{
			auto ptr = std::shared_ptr<DelayedBehavior>(new DelayedBehavior(delay, baseBehavior));
			EventManager::Subscribe(EventType::GAME_START, ptr);
			return ptr;
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;
		void HandleEvent(const Event& event) override;

	private:
		DelayedBehavior(float delay, const std::shared_ptr<GhostMoveBehavior>& pBaseBehavior);
		float m_Delay, m_RemainingTime;
		std::shared_ptr<GhostMoveBehavior> m_pBaseBehavior;
	};
}
