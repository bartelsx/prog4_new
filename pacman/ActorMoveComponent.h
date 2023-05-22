#pragma once
#include <BaseComponent.h>

#include "GameBoardModel.h"
#include "MoveComponent.h"

namespace dae
{
    class ActorMoveComponent : public MoveComponent
    {
    public:
	    ~ActorMoveComponent() override = default;
	    ActorMoveComponent(const ActorMoveComponent& other) = delete;
	    ActorMoveComponent(ActorMoveComponent&& other) = delete;
	    ActorMoveComponent& operator=(const ActorMoveComponent& other) = delete;
	    ActorMoveComponent& operator=(ActorMoveComponent&& other) = delete;

		static std::shared_ptr<ActorMoveComponent> Create(std::shared_ptr<MoveComponent> pBase, std::shared_ptr<GameBoardModel> pModel)
		{
			return std::shared_ptr<ActorMoveComponent>(new ActorMoveComponent(pBase, pModel));
		}

		void SetSpeed(const float speed) override { m_pBase->SetSpeed(speed); }
		void SetDirection(const glm::vec2& direction) override { m_pBase->SetDirection(direction); }

		void Update(float deltaTime) override;

    private:
	    ActorMoveComponent(std::shared_ptr<MoveComponent> pBase, std::shared_ptr<GameBoardModel> pModel);
		std::shared_ptr<MoveComponent> m_pBase;
		std::shared_ptr<GameBoardModel> m_pModel;
    };
}

