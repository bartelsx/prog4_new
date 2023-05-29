#pragma once
#include <memory>
#include <vector>

#include "GameBoardModel.h"

struct PathNode;

namespace dae
{

	//Finds a path on the board using A* algorithm
	class PathFinder
	{
	public:
		PathFinder(std::shared_ptr<GameBoardModel>pBoardModel):m_pBoardModel(pBoardModel)
		{}

		~PathFinder() = default;
		PathFinder(const PathFinder& other) = delete;
		PathFinder(PathFinder&& other) = delete;
		PathFinder& operator=(const PathFinder& other) = delete;
		PathFinder& operator=(PathFinder&& other) = delete;

		std::vector<int> FindPath(int start, int target) const;

	private:
		std::vector<int> ReconstructPath(PathNode* current) const;
		static PathNode* FindMinFCell(const std::vector<PathNode*>& openSet);

		std::shared_ptr<GameBoardModel> m_pBoardModel;

	};
}
