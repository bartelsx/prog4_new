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

		static std::shared_ptr<ActorMoveComponent> Create(std::shared_ptr<GameBoardModel> pModel)
		{
			return std::shared_ptr<ActorMoveComponent>(new ActorMoveComponent( pModel));
		}

		void Update(float deltaTime) override;
    protected:
	    ActorMoveComponent( std::shared_ptr<GameBoardModel> pModel);
    private:
		std::shared_ptr<GameBoardModel> m_pBoardModel;
    };
}

