#pragma once
#include "GhostMoveBehavior.h"

namespace dae
{

	class SequentialBehavior : public GhostMoveBehavior
	{
	public:
		~SequentialBehavior() override = default;
		SequentialBehavior(const SequentialBehavior& other) = delete;
		SequentialBehavior(SequentialBehavior&& other) = delete;
		SequentialBehavior& operator=(const SequentialBehavior& other) = delete;
		SequentialBehavior& operator=(SequentialBehavior&& other) = delete;

		static std::shared_ptr<SequentialBehavior> Create();
		
		void Add(const std::shared_ptr<GhostMoveBehavior>& pBehavior, float duration);
		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		SequentialBehavior() = default;
		std::vector< std::pair<std::shared_ptr<GhostMoveBehavior>, float>  > m_Behaviors{};

		int m_BehaviorIdx{-1};
		float m_RemainingTime{};
	};
}
