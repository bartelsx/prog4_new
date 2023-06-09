#include "GameBoardModel.h"
#include <fstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <rapidjson/document.h>
#include "TextureComponent.h"

using namespace dae;

inline bool operator ==(const int& lhs, const TileValue& rhs) { return lhs == static_cast<int>(rhs); }
inline bool operator !=(const int& lhs, const TileValue& rhs) { return !(lhs == rhs); }

void GameBoardModel::LoadFromJsonFile(const std::string& path)
{
	ReadJsonFile(path);

	m_PillCount = 0;
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{

			float posX = float(col * m_TileSize);
			float posY = float(row * m_TileSize);


			int idx = GetIdx(col, row);
			if (m_Grid[idx] != 0)
			{
				auto object{ dae::GameObject::Create() };
				object->SetPosition(posX, posY);
				switch (m_Grid[idx])
				{
				case 2:
				case 3:
					++m_PillCount;
					break;
				case 6:
					m_GhostSpawnLocations.emplace_back(glm::vec2(posX, posY));
					m_Grid[idx] = 4;
					break;
				case 7:
					m_PacmanSpawnLocation = glm::vec2(posX, posY);
					m_Grid[idx] = 4;
					break;
				case 8:
					m_Teleports.emplace_back(idx);
					m_Grid[idx] = 4;
					break;

				default:
					break;
				}
			}
		}
	}
}

void GameBoardModel::ChangeTileValue(glm::vec2 position, TileValue newValue)
{
	auto idx = GetIdx(position, false);
	auto oldValue = m_Grid[idx];
	if ((oldValue == TileValue::Boost || oldValue == TileValue::Pill) && newValue != TileValue::Boost && newValue != TileValue::Pill)
	{
		--m_PillCount;
		if (m_PillCount <= 0)
		{
			EventManager::Publish(EventType::GAME_OVER); //TODO: should become LEVEL_COMPLETE
		}
	}
	m_Grid[idx] = int(newValue);
}

int GameBoardModel::CalculateDistance(int firstIdx, int secondIdx) const
{
	const auto cr1 = GetColumnRow(firstIdx);
	const auto cr2 = GetColumnRow(secondIdx);

	//return manhattan-distance
	return abs(cr1.x - cr2.x) + abs(cr1.y - cr2.y);
}

void GameBoardModel::AddIfValid(int col, int row, std::vector<int>& result) const
{
	if (row >= 0 && row < m_Rows && col >= 0 && col < m_Columns)
	{
		auto idx = GetIdx(col, row);
		if (GetTileValue(idx) != TileValue::Wall)
		{
			result.emplace_back(idx);
		}
	}
}

std::vector<int> GameBoardModel::GetAdjacentAccessibleCells(int cellId) const
{
	std::vector<int> result{};

	auto cr = GetColumnRow(cellId);

	AddIfValid(cr.x, cr.y - 1, result);
	AddIfValid(cr.x, cr.y + 1, result);
	AddIfValid(cr.x - 1, cr.y, result);
	AddIfValid(cr.x + 1, cr.y, result);

	if (IsTeleport(cellId))
	{
		result.emplace_back(GetPairedTeleport(cellId));
	}

	return result;
}

void GameBoardModel::ReadJsonFile(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	// Read the entire file into a string
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	rapidjson::Document doc;
	if (doc.Parse(str.c_str()).HasParseError()) {
		std::cerr << "Failed to parse JSON" << std::endl;
		return;
	}

	// Get the values from the document
	m_Columns = doc["width"].GetInt();
	m_Rows = doc["height"].GetInt();
	const rapidjson::Value& grid = doc["grid"];

	// Print the values
	//std::cout << "Width: " << m_Width << std::endl;
	//std::cout << "Height: " << m_Height << std::endl;
	//std::cout << "Grid:" << std::endl;
	for (rapidjson::SizeType i = 0; i < grid.Size(); i++) {
		for (rapidjson::SizeType j = 0; j < grid[i].Size(); j++) {
			//std::cout << grid[i][j].GetInt() << " ";
			m_Grid.emplace_back(grid[i][j].GetInt());
		}
		//std::cout << std::endl;
	}
}

int GameBoardModel::GetIdx(int col, int row) const
{
	if (row < 0 || col < 0 || row >= m_Rows || col >= m_Columns)
	{
		assert(false);
		return 0;
	}
	return row * m_Columns + col;
}

int GameBoardModel::GetIdx(const glm::vec2 location, bool applyCenterOffset = false) const
{
	auto offset = applyCenterOffset ? m_TileSize * .5f : 0.f;
	return GetIdx(static_cast<int>((location.x + offset) / m_TileSize), static_cast<int>((location.y + offset)/ m_TileSize));
}

glm::vec2 GameBoardModel::GetCenter(int col, int row) const
{
	return glm::vec2{ col * m_TileSize + m_TileSize * 0.5f, row * m_TileSize + m_TileSize * 0.5f };
}

glm::vec2 GameBoardModel::GetCenter(int idx) const
{
	auto offset = GetOffset(idx);
	return glm::vec2{ offset.x + m_TileSize * 0.5f, offset.y + m_TileSize * 0.5f };
}

glm::vec2 GameBoardModel::GetOffset(int col, int row) const
{
	return glm::vec2{ col * m_TileSize, row * m_TileSize };
}

glm::vec2 GameBoardModel::GetOffset(int idx) const
{
	auto cr = GetColumnRow(idx);
	return glm::vec2{ cr.x * m_TileSize, cr.y * m_TileSize };
}

glm::ivec2 GameBoardModel::GetColumnRow(const glm::vec2 location) const
{
	return glm::ivec2{ int(location.x / m_TileSize),int(location.y / m_TileSize) };
}

glm::ivec2 GameBoardModel::GetColumnRow(const int idx) const
{
	const int row = idx / m_Columns;
	const int col = idx % m_Columns;
	return glm::ivec2(col, row);
}


TileValue GameBoardModel::GetTileValue(int idx) const
{
	return static_cast<TileValue>(m_Grid[idx]);
}

TileValue GameBoardModel::GetTileValue(int col, int row) const
{
	return GetTileValue(GetIdx(col, row));
}

TileValue GameBoardModel::GetTileValue(const glm::vec2 location) const
{
	return static_cast<TileValue>(m_Grid[GetIdx(location)]);
}

bool GameBoardModel::IsPlayerAllowedAtLocation(glm::vec2 location) const
{
	return IsTileAccessible(location)
		&& IsTileAccessible({ location.x + m_TileSize - 1, location.y + m_TileSize - 1 })
		&& IsTileAccessible({ location.x , location.y + m_TileSize - 1 })
		&& IsTileAccessible({ location.x + m_TileSize - 1, location.y });
}

bool GameBoardModel::IsTeleport(int cellIdx) const
{
	auto it = std::find(m_Teleports.begin(), m_Teleports.end(), cellIdx);
	return it < m_Teleports.end();
}

int GameBoardModel::GetPairedTeleport(int cellIdx) const
{
	auto it = std::find(m_Teleports.begin(), m_Teleports.end(), cellIdx);
	if (it < m_Teleports.end())
	{
		int thisTeleportIdx = static_cast<int>( std::distance(m_Teleports.begin(), it));
		int otherTeleportIdx = thisTeleportIdx ^ 1; //flip low order bit
		if (otherTeleportIdx < m_Teleports.size())
		{
			return m_Teleports[otherTeleportIdx];
		}
	}
	assert(false);
	return cellIdx;
}

bool GameBoardModel::IsTileAccessible(glm::vec2 location) const
{
	int row = int(location.y / m_TileSize);
	int col = int(location.x / m_TileSize);
	return IsTileAccessible(col, row);
}

bool GameBoardModel::IsTileAccessible(int col, int row) const
{
	const auto tileValue = m_Grid[GetIdx(col, row)];
	return tileValue != int(TileValue::Wall);
}

glm::vec2 GameBoardModel::GetPlayerSpawnLocation() const
{
	return
		m_PacmanSpawnLocation;
}

size_t GameBoardModel::GetGhostsCount() const
{
	return m_GhostSpawnLocations.size();
}

glm::vec2 GameBoardModel::GetGhostSpawnLocation(int ghostIdx) const
{
	return  m_GhostSpawnLocations[ghostIdx];
}
