#include "PathFinder.h"

#include <iostream>
#include <ostream>

using namespace dae;


struct PathNode
{
	int cellId;  // Coordinates of the cell
	int f, g, h;  // Evaluation values for A* algorithm
	PathNode* parent;  // Parent cell in the path

	PathNode(int id) : cellId(id), f(0), g(0), h(0), parent(nullptr) {}

	bool IsEqual(const PathNode& other) const { return other.cellId == cellId; }
};

inline bool operator==(const PathNode& lhs, const PathNode& rhs) { return lhs.IsEqual(rhs); }
inline bool operator!=(const PathNode& lhs, const PathNode& rhs) { return !lhs.IsEqual(rhs); }

// Function to reconstruct the path from start to end
std::vector<int> PathFinder::ReconstructPath(PathNode* current) const
{
	std::vector<int> path;
	while (current != nullptr) {
		path.push_back(current->cellId);
		current = current->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

// Function to find the cell with the minimum f value in the open set
PathNode* PathFinder::FindMinFCell(const std::vector<PathNode*>& openSet) {
	PathNode* minCell = openSet[0];
	for (PathNode* cell : openSet) {
		if (cell->f < minCell->f) {
			minCell = cell;
		}
	}
	return minCell;
}

// A* algorithm to find the best path
std::vector<int> PathFinder::FindPath(int startCellId, int targetCellId) const
{
	auto startNode = new PathNode{ startCellId };
	// Create a vector of open and closed cells
	std::vector<PathNode*> openSet;
	std::vector<PathNode*> closedSet;

	// Add the start cell to the open set
	openSet.push_back(startNode);

	while (!openSet.empty()) {
		// Find the cell with the minimum f value in the open set
		PathNode* current = FindMinFCell(openSet);

		// Remove the current cell from the open set
		auto it = std::find(openSet.begin(), openSet.end(), current);
		openSet.erase(it);

		// Add the current cell to the closed set
		closedSet.push_back(current);

		// Check if the current cell is the target cell
		if (current->cellId == targetCellId) 
		{
			std::vector<int> path = ReconstructPath(current);

			// Clean up memory
			for (PathNode* cell : openSet) {
				delete cell;
			}
			for (PathNode* cell : closedSet) {
				delete cell;
			}

			return path;
		}

		// Generate the adjacent cells
		std::vector<int> adjacentCells = m_pBoardModel->GetAdjacentAccessibleCells(current->cellId);

		// Process adjacent cells
		for (int adjacentIdx : adjacentCells)
		{
			// Skip if the adjacent cell is already in the closed set
			bool isInClosed{};
			for (auto closed : closedSet)
			{

				if (closed->cellId == adjacentIdx)
				{
					isInClosed = true;
					break;
				}
			}
			if (isInClosed)
			{
				continue;
			}

			auto adjacent = new PathNode{ adjacentIdx };
			int newG = current->g + 1;  // Assuming a constant cost of movement
			int newH = m_pBoardModel->CalculateDistance(adjacent->cellId, current->cellId);
			int newF = newG + newH;

			// Check if the adjacent cell is already in the open set
			bool isOpen = false;
			auto openIt = std::find(openSet.begin(), openSet.end(), adjacent);
			if (openIt != openSet.end())
			{
				isOpen = true;
			}

			// If the adjacent cell is not in the open set or has a lower f value, update its values and set the current cell as its parent
			if (!isOpen || newF < (*openIt)->f)
			{
				adjacent->g = newG;
				adjacent->h = newH;
				adjacent->f = newF;
				adjacent->parent = current;

				// If the adjacent cell is not in the open set, add it
				if (!isOpen) {
					openSet.emplace_back(adjacent);
				}
			}
			else
			{
				delete adjacent;  // Clean up memory if the adjacent cell is not used
			}
		}
	}
	for (PathNode* cell : closedSet) {
		delete cell;
	}
	// No path found
	std::cout << "No path found!" << std::endl;
	return std::vector<int>();
}

