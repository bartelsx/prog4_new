#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "GhostMoveBehavior.h"
#include "PathFinder.h"

namespace dae
{
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

		static std::shared_ptr<ChasePacmanBehavior> Create(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pGameModel)
		{
			return std::shared_ptr<ChasePacmanBehavior>(new ChasePacmanBehavior(pPacmanObj, pGameModel));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel);

		float m_Speed{ .8f };
		const std::shared_ptr<GameObject> m_pPacmanObj;
		const std::shared_ptr<GameBoardModel> m_pBoardModel;
		std::shared_ptr<PathFinder> m_pathFinder;
		std::vector<int> m_PrevPath{};
	};
}
