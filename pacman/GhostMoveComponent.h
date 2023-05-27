#pragma once
#include "ActorMoveComponent.h"

namespace dae
{
	class GhostMoveBehavior;

	class GhostMoveComponent : public ActorMoveComponent
	{
	public:
		static std::shared_ptr<GhostMoveComponent> Create(const std::shared_ptr<GhostMoveBehavior> chaseBehavior, const std::shared_ptr<GameBoardModel> pModel)
		{
			return std::shared_ptr<GhostMoveComponent>(new GhostMoveComponent(chaseBehavior, pModel));
		}
		~GhostMoveComponent() = default;
		GhostMoveComponent(const GhostMoveComponent& other) = delete;
		GhostMoveComponent(GhostMoveComponent&& other) = delete;
		GhostMoveComponent& operator=(const GhostMoveComponent& other) = delete;
		GhostMoveComponent& operator=(GhostMoveComponent&& other) = delete;

		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const override;
	private:
		GhostMoveComponent(const std::shared_ptr<GhostMoveBehavior> chaseBehavior, const std::shared_ptr<GameBoardModel> pModel);
		std::shared_ptr<GhostMoveBehavior> m_pChaseBehavior;
	};
}

