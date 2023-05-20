#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "TextureManager.h"

namespace dae
{
	enum class TileValue
	{
		Wall = 1,
		Pill = 2,
		Boost = 3,
		Path = 4,
		Gate = 5,
	};

	class GameBoardModel
	{
	public:
		GameBoardModel() = default;
		~GameBoardModel() = default;
		GameBoardModel(const GameBoardModel& other) = delete;
		GameBoardModel(GameBoardModel&& other) = delete;
		GameBoardModel& operator=(const GameBoardModel& other) = delete;
		GameBoardModel& operator=(GameBoardModel&& other) = delete;

		void ReadJsonFile(const std::string& filename);
		int GetIdx(int row, int col) const;

		int GetTileSize() const { return int(m_TileSize); }
		int GetWidth() const { return int(m_Columns * m_TileSize); }
		int GetHeight() const { return int(m_Rows * m_TileSize); }

		int GetRows() const { return m_Rows; }
		int GetColumns() const { return m_Columns; } 
		glm::vec2 GetOffset(int row, int col) const;

		TileValue GetTileValue(int row, int col) const;

		bool IsPlayerAllowedAtLocation(glm::vec2 location) const;
		bool IsTileAtLocationAccessible(glm::vec2 location) const;

		glm::vec2 GetPlayerSpawnLocation() const;
		glm::vec2 GetGhostSpawnLocation(int ghostIdx) const;
		void LoadFromJsonFile(const std::string& path);

	private:
		std::vector<int> m_Grid;
		float m_TileSize = 16;
		int m_Columns{};
		int m_Rows{};

		std::vector<glm::vec2> m_ghostSpawnLocations{};
		glm::vec2 m_pacmanSpawnLocation{};

	};
}
