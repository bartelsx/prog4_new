#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "GhostMoveBehavior.h"

struct PathNode;

namespace dae
{
	class GameObject;
	class GameBoardModel;

	class ChasePacmanBehavior : public GhostMoveBehavior
	{

	public:
		~ChasePacmanBehavior() override = default;
		ChasePacmanBehavior(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior(ChasePacmanBehavior&& other) = delete;
		ChasePacmanBehavior& operator=(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior& operator=(ChasePacmanBehavior&& other) = delete;

		static std::shared_ptr<ChasePacmanBehavior> Create(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pGameModel)
		{
			return std::shared_ptr<ChasePacmanBehavior>(new ChasePacmanBehavior(pPacmanObj, pGameModel));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel);
		std::vector<int> FindPath(const PathNode& start, const PathNode& target);

		bool IsValidCell(int x, int y);
		bool IsTargetCell(int col, int row, const PathNode& target);
		std::vector<int> ReconstructPath(PathNode* current);
		PathNode* FindMinFCell(const std::vector<PathNode*>& openSet);
		float m_Speed{ 1.05f };
		const std::shared_ptr<GameObject> m_pPacmanObj;
		const std::shared_ptr<GameBoardModel> m_pBoardModel;
	};
}
