#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "EventManager.h"
#include "EventType.h"
#include "Observer.h"
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
		int GetIdx(int row, int col) const;
		int GetIdx(const glm::vec2 location) const;

		int GetTileSize() const { return int(m_TileSize); }
		int GetWidth() const { return int(m_Columns * m_TileSize); }
		int GetHeight() const { return int(m_Rows * m_TileSize); }

		int GetRows() const { return m_Rows; }
		int GetColumns() const { return m_Columns; } 
		glm::vec2 GetOffset(int row, int col) const;

		TileValue GetTileValue(int row, int col) const;
		TileValue GetTileValue(const glm::vec2 location) const;

		bool IsPlayerAllowedAtLocation(glm::vec2 location) const;
		bool IsTileAtLocationAccessible(glm::vec2 location) const;

		glm::vec2 GetPlayerSpawnLocation() const;
		glm::vec2 GetGhostSpawnLocation(int ghostIdx) const;
		void LoadFromJsonFile(const std::string& path);

		//void Notify(Event& event) override;
		void HandleActorMoved(Event& event);
		void ChangeTileValue(glm::vec2 position, TileValue newValue);

		static std::shared_ptr<GameBoardModel> Create()
		{
			auto sptr = std::shared_ptr<GameBoardModel>(new GameBoardModel());
			return sptr;
		}

	private:
		GameBoardModel() = default;
		std::vector<int> m_Grid;
		float m_TileSize = 16;
		int m_Columns{};
		int m_Rows{};

		std::vector<glm::vec2> m_GhostSpawnLocations{};
		glm::vec2 m_PacmanSpawnLocation{};

	};
}
