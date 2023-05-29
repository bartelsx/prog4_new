#pragma once
#include "GhostMoveBehavior.h"

namespace dae
{
	class GameState;

	class FleeBehavior : public GhostMoveBehavior
	{
	public:
		~FleeBehavior() override = default;
		FleeBehavior(const FleeBehavior& other) = delete;
		FleeBehavior(FleeBehavior&& other) = delete;
		FleeBehavior& operator=(const FleeBehavior& other) = delete;
		FleeBehavior& operator=(FleeBehavior&& other) = delete;

		static std::shared_ptr<FleeBehavior> Create(const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameState>& pGameState)
		{
			return std::shared_ptr<FleeBehavior>(new FleeBehavior(pBoardModel, pGameState));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		FleeBehavior(const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameState>& pGameState);
		int CalcDistance(int candidateCol, int candidateRow, int pacmanCol, int pacmanRow) const;

		std::shared_ptr<GameBoardModel> m_pBoardModel;
		std::shared_ptr<GameState> m_pGameState;
		float m_speed{.5f};
	};
}
