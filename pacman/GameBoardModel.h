#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "ActorComponent.h"
#include "ChasePacmanBehavior.h"
#include "Events.h"
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

	class GameBoardModel : /*public Observer,*/ std::enable_shared_from_this<GameBoardModel>
	{
	public:
		GameBoardModel(const GameBoardModel& other) = delete;
		GameBoardModel(GameBoardModel&& other) = delete;
		GameBoardModel& operator=(const GameBoardModel& other) = delete;
		GameBoardModel& operator=(GameBoardModel&& other) = delete;

		void ReadJsonFile(const std::string& filename);
		int GetIdx(int col, int row) const;
		int GetIdx(const glm::vec2 location, bool applyCenterOffset) const;

		int GetTileSize() const { return int(m_TileSize); }
		int GetWidth() const { return int(m_Columns * m_TileSize); }
		int GetHeight() const { return int(m_Rows * m_TileSize); }

		int GetRows() const { return m_Rows; }
		int GetColumns() const { return m_Columns; } 

		glm::vec2 GetOffset(int col, int row) const;
		glm::vec2 GetOffset(int idx) const;

		glm::vec2 GetCenter(int col, int row) const;
		glm::vec2 GetCenter(int idx) const ;

		TileValue GetTileValue(int col, int row) const;
		TileValue GetTileValue(const glm::vec2 location) const;

		glm::ivec2 GetColumnRow(const glm::vec2 location) const;
		glm::ivec2 GetColumnRow(const int idx) const;
		TileValue GetTileValue(int idx) const;

		bool IsPlayerAllowedAtLocation(glm::vec2 location) const;
		bool IsTileAccessible(glm::vec2 location) const;
		bool IsTileAccessible(int col, int row) const;

		glm::vec2 GetPlayerSpawnLocation() const;
		size_t GetGhostsCount() const;
		glm::vec2 GetGhostSpawnLocation(int ghostIdx) const;
		void LoadFromJsonFile(const std::string& path);
		void ChangeTileValue(glm::vec2 position, TileValue newValue);

		int CalculateDistance(int firstIdx, int secondIdx) const;
		std::vector<int> GetAdjacentAccessibleCells(int cellId) const;

		bool IsTeleport(int cellIdx) const;
		int GetPairedTeleport(int cellIdx) const;

		static std::shared_ptr<GameBoardModel> Create()
		{
			auto sptr = std::shared_ptr<GameBoardModel>(new GameBoardModel());
			return sptr;
		}

	private:
		GameBoardModel() = default;
		void AddIfValid(int col, int row, std::vector<int>& result) const;

		std::vector<int> m_Grid;
		float m_TileSize = 16;
		int m_Columns{};
		int m_Rows{};

		std::vector<glm::vec2> m_GhostSpawnLocations{};
		glm::vec2 m_PacmanSpawnLocation{};
		std::vector <int> m_Teleports{};
		
	};
}
