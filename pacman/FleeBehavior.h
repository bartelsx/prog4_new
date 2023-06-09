#pragma once
#include "GhostMoveBehavior.h"
#include "StartGameCommand.h"

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

		static std::shared_ptr<FleeBehavior> Create(const GameMode gameMode, const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameObject>& pPacWomanObj)
		{
			return std::shared_ptr<FleeBehavior>(new FleeBehavior(gameMode, pBoardModel, pPacmanObj, pPacWomanObj));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		FleeBehavior(const GameMode gameMode, const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameObject>& pPacWomanObj);
		int CalcDistance(int candidateCol, int candidateRow, int pacmanCol, int pacmanRow) const;

		const GameMode m_GameMode;
		const std::shared_ptr<GameBoardModel> m_pBoardModel;
		const std::shared_ptr<GameObject> m_pPacmanObj;
		const std::shared_ptr<GameObject> m_pPacWomanObj;

		float m_speed{.5f};
	};
}
