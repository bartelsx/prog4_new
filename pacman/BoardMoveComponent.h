#pragma once
#include <BaseComponent.h>

#include "GameBoardModel.h"
#include "MoveComponent.h"

namespace dae
{
    class BoardMoveComponent : public MoveComponent
    {
    public:
	    BoardMoveComponent(std::shared_ptr<GameBoardModel> pModel);
	    ~BoardMoveComponent() override = default;
	    BoardMoveComponent(const BoardMoveComponent& other) = delete;
	    BoardMoveComponent(BoardMoveComponent&& other) = delete;
	    BoardMoveComponent& operator=(const BoardMoveComponent& other) = delete;
	    BoardMoveComponent& operator=(BoardMoveComponent&& other) = delete;

		void Update(float deltaTime) override;

    private:
		std::shared_ptr<GameBoardModel> m_pModel;
    };
}

