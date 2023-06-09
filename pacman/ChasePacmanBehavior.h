#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "GhostMoveBehavior.h"
#include "PathFinder.h"
#include "StartGameCommand.h"

namespace dae
{
	class TargetSelector;
	class GameObject;
	class GameBoardModel;
	class PathFinder;

	class ChasePacmanBehavior : public GhostMoveBehavior
	{

	public:
		~ChasePacmanBehavior() override = default;
		ChasePacmanBehavior(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior(ChasePacmanBehavior&& other) = delete;
		ChasePacmanBehavior& operator=(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior& operator=(ChasePacmanBehavior&& other) = delete;

		static std::shared_ptr<ChasePacmanBehavior> Create(const GameMode gameMode, const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameObject>& pPacWomanObj, const std::shared_ptr<GameBoardModel>& pGameModel, const std::shared_ptr<TargetSelector>& pTargetSelector)
		{
			return std::shared_ptr<ChasePacmanBehavior>(new ChasePacmanBehavior(gameMode, pPacmanObj, pPacWomanObj, pGameModel, pTargetSelector));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		ChasePacmanBehavior(const GameMode gameMode, const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameObject>& pPacWomanObj, const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<TargetSelector>& pTargetSelector);

		float m_Speed{ .8f };
		const GameMode m_GameMode;
		const std::shared_ptr<GameObject> m_pPacmanObj;
		const std::shared_ptr<GameObject> m_pPacWomanObj;
		const std::shared_ptr<GameBoardModel> m_pBoardModel;
		const std::shared_ptr<TargetSelector> m_pTargetSelector;
		std::shared_ptr<PathFinder> m_pathFinder;
		std::vector<int> m_PrevPath{};
	};
}
