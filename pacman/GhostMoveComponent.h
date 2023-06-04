#pragma once
#include "ActorMoveComponent.h"

namespace dae
{
	class GhostMoveBehavior;

	class GhostMoveComponent : public ActorMoveComponent
	{
	public:
		static std::shared_ptr<GhostMoveComponent> Create(const std::shared_ptr<GhostMoveBehavior>& behavior, const std::shared_ptr<GameBoardModel>& pModel)
		{
			auto ptr = std::shared_ptr<GhostMoveComponent>(new GhostMoveComponent(behavior, pModel));
			return ptr;
		}

		~GhostMoveComponent() override = default;
		GhostMoveComponent(const GhostMoveComponent& other) = delete;
		GhostMoveComponent(GhostMoveComponent&& other) = delete;
		GhostMoveComponent& operator=(const GhostMoveComponent& other) = delete;
		GhostMoveComponent& operator=(GhostMoveComponent&& other) = delete;

		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const override;

	private:
		GhostMoveComponent(const std::shared_ptr<GhostMoveBehavior>& behavior, const std::shared_ptr<GameBoardModel>& pModel);
		std::shared_ptr<GhostMoveBehavior> m_pBehavior;
	};
}

