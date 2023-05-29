#pragma once
#include "ActorMoveComponent.h"

namespace dae
{
	class GhostMoveBehavior;

	class GhostMoveComponent : public ActorMoveComponent, public Observer
	{
	public:
		static std::shared_ptr<GhostMoveComponent> Create(const std::shared_ptr<GhostMoveBehavior>& chaseBehavior, const std::shared_ptr<GhostMoveBehavior>& fleeBehavior, const std::shared_ptr<GameBoardModel>& pModel)
		{
			auto ptr = std::shared_ptr<GhostMoveComponent>(new GhostMoveComponent(chaseBehavior, fleeBehavior, pModel));
			EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
			EventManager::Subscribe(EventType::END_BOOST, ptr);
			EventManager::Subscribe(EventType::ENEMY_DIED, ptr);
			return ptr;
		}
		~GhostMoveComponent() override = default;
		GhostMoveComponent(const GhostMoveComponent& other) = delete;
		GhostMoveComponent(GhostMoveComponent&& other) = delete;
		GhostMoveComponent& operator=(const GhostMoveComponent& other) = delete;
		GhostMoveComponent& operator=(GhostMoveComponent&& other) = delete;

		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const override;
		void HandleEvent(const Event& event) override;

	private:
		GhostMoveComponent(const std::shared_ptr<GhostMoveBehavior>& chaseBehavior, const std::shared_ptr<GhostMoveBehavior>& fleeBehavior, const std::shared_ptr<GameBoardModel>& pModel);
		std::shared_ptr<GhostMoveBehavior> m_pChaseBehavior;
		std::shared_ptr<GhostMoveBehavior> m_pFleeBehavior;
		std::shared_ptr<GhostMoveBehavior> m_pCurrentBehavior;
	};
}

