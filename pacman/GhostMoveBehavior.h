#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include <vector>

#include "ActorComponent.h"
#include "ActorComponent.h"
#include "ActorComponent.h"
#include "ActorComponent.h"


struct PathNode;

namespace dae
{
	class GameBoardModel;
	class GameObject;

	class GhostMoveBehavior
	{
	public:

		virtual glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) = 0;
	private:

	};

	class ChasePacmanBehavior : public GhostMoveBehavior 
	{
	
	public:
		static std::shared_ptr<ChasePacmanBehavior> Create(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pGameModel)
		{
			return std::shared_ptr<ChasePacmanBehavior>(new ChasePacmanBehavior(pPacmanObj,pGameModel));
		}
		~ChasePacmanBehavior() = default;
		ChasePacmanBehavior(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior(ChasePacmanBehavior&& other) = delete;
		ChasePacmanBehavior& operator=(const ChasePacmanBehavior& other) = delete;
		ChasePacmanBehavior& operator=(ChasePacmanBehavior&& other) = delete;
		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;
		std::vector<int> FindPath(const PathNode& start, const PathNode& target);
	private:
		ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel);

		bool IsValidCell(int x, int y);
		bool IsTargetCell(int col, int row, const PathNode& target);
		std::vector<int> ReconstructPath(PathNode* current);
		PathNode* FindMinFCell(const std::vector<PathNode*>& openSet);

		const std::shared_ptr<GameObject> m_pPacmanObj;
		const std::shared_ptr<GameBoardModel> m_pBoardModel;
	};
}

