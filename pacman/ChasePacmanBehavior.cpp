
#include "ChasePacmanBehavior.h"

#include <iostream>
#include <ostream>
#include <vector>

#include "GameBoardModel.h"

struct PathNode;

using namespace dae;

struct PathNode {
	int col, row;  // Coordinates of the cell
	int f, g, h;  // Evaluation values for A* algorithm
	PathNode* parent;  // Parent cell in the path

	PathNode(int x, int y) : col(x), row(y), f(0), g(0), h(0), parent(nullptr) {}
	bool IsEqual(const PathNode& other) const { return other.col == col && other.row == row; }
	// Calculate the heuristic value to the target cell
	int calculateHeuristic(const PathNode& target) const {
		return std::abs(col - target.col) + std::abs(row - target.row);
	}
};

inline bool operator==(const PathNode& lhs, const PathNode& rhs) { return lhs.IsEqual(rhs); }
inline bool operator!=(const PathNode& lhs, const PathNode& rhs) { return !lhs.IsEqual(rhs); }

ChasePacmanBehavior::ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel)
	: GhostMoveBehavior()
	, m_pPacmanObj(pPacmanObj)
	, m_pBoardModel(pBoardModel)
{
}

glm::vec2 ChasePacmanBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	auto colRow = m_pBoardModel->GetColumnRow(currentGhostLoc);

	PathNode startCell{ colRow.x,colRow.y };

	colRow = m_pBoardModel->GetColumnRow(m_pPacmanObj->GetPosition());
	PathNode targetCell{ colRow.x,colRow.y };

	auto path = FindPath(startCell, targetCell);
	if (path.size() <= 0)
	{
		return currentGhostLoc;
	}
	auto target = path.size() > 1 ? path[1] : path[0];
	auto distance = deltaTime * 100 * m_Speed;
	auto targetLoc = m_pBoardModel->GetOffset(target);
	auto newX = currentGhostLoc.x + (targetLoc.x < currentGhostLoc.x ? -distance : targetLoc.x > currentGhostLoc.x ? +distance : 0);
	auto newY = currentGhostLoc.y + (targetLoc.y < currentGhostLoc.y ? -distance : targetLoc.y > currentGhostLoc.y ? +distance : 0);
	//std::cout << newX << " " << newY << " " << distance<<"\n";
	return glm::vec2{ newX,newY };
}


// Function to check if a cell is the target cell
bool ChasePacmanBehavior::IsTargetCell(int col, int row, const PathNode& target) {
	return (col == target.col && row == target.row);
}

// Function to reconstruct the path from start to end
std::vector<int> ChasePacmanBehavior::ReconstructPath(PathNode* current) {
	std::vector<int> path;
	while (current != nullptr) {
		path.push_back(m_pBoardModel->GetIdx(current->row, current->col));
		current = current->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

// Function to find the cell with the minimum f value in the open set
PathNode* ChasePacmanBehavior::FindMinFCell(const std::vector<PathNode*>& openSet) {
	PathNode* minCell = openSet[0];
	for (PathNode* cell : openSet) {
		if (cell->f < minCell->f) {
			minCell = cell;
		}
	}
	return minCell;
}

// A* algorithm to find the best path
std::vector<int> ChasePacmanBehavior::FindPath(const PathNode& start, const PathNode& target)
{
	// Create a vector of open and closed cells
	std::vector<PathNode*> openSet;
	std::vector<PathNode*> closedSet;

	// Add the start cell to the open set
	openSet.push_back(new PathNode(start.col, start.row));

	while (!openSet.empty()) {
		// Find the cell with the minimum f value in the open set
		PathNode* current = FindMinFCell(openSet);

		// Remove the current cell from the open set
		auto it = std::find(openSet.begin(), openSet.end(), current);
		openSet.erase(it);

		// Add the current cell to the closed set
		closedSet.push_back(current);

		// Check if the current cell is the target cell
		if (IsTargetCell(current->col, current->row, target)) {
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
		std::vector<PathNode*> adjacentCells;
		if (current->col > 0) adjacentCells.emplace_back(new PathNode(current->col - 1, current->row));
		if (current->row > 0) adjacentCells.emplace_back(new PathNode(current->col, current->row - 1));
		if (current->col + 1 < m_pBoardModel->GetColumns()) adjacentCells.emplace_back(new PathNode(current->col + 1, current->row));
		if (current->row + 1 < m_pBoardModel->GetRows()) adjacentCells.emplace_back(new PathNode(current->col, current->row + 1));

		// Process adjacent cells
		for (PathNode* adjacent : adjacentCells)
		{
			// Skip if adjacent cell is a wall
			if (m_pBoardModel->GetTileValue(adjacent->row, adjacent->col) == TileValue::Wall)
			{
				delete adjacent;
				continue;
			}

			// Skip if the adjacent cell is already in the closed set
			bool isInClosed{};
			for (auto closed : closedSet)
			{

				if (closed->IsEqual(*adjacent))
				{
					delete adjacent;
					isInClosed = true;
					break;
				}
			}
			if (isInClosed)
			{
				continue;
			}
			int newG = current->g + 1;  // Assuming a constant cost of movement
			int newH = adjacent->calculateHeuristic(target);
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
