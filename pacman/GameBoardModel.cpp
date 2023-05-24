#include "GameBoardModel.h"

#include <fstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <rapidjson/document.h>

#include "EventType.h"
#include "TextureComponent.h"

using namespace dae;
void GameBoardModel::LoadFromJsonFile(const std::string& path)
{
	ReadJsonFile(path);

	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{

			float posX = float(col * m_TileSize);
			float posY = float(row * m_TileSize);


			int idx = GetIdx(row,col);
			if (m_Grid[idx] != 0)
			{
				auto object{ dae::GameObject::Create() };
				object->SetPosition(posX, posY);
				switch (m_Grid[idx])
				{
				case 6:
					m_GhostSpawnLocations.push_back(glm::vec2(posX, posY));
					m_Grid[idx] = 4;
					break;
				case 7:
					m_PacmanSpawnLocation = glm::vec2(posX, posY);
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
	auto idx = GetIdx(position);
	m_Grid[idx] = int(newValue);
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
			m_Grid.push_back(grid[i][j].GetInt());
		}
		//std::cout << std::endl;
	}
}

int GameBoardModel::GetIdx(int row, int col) const
{
	if (row < 0 || col<0 || row>=m_Rows || col>=m_Columns)
	{
		assert(false);
		return 0;
	}
	return row * m_Columns + col;
}

int GameBoardModel::GetIdx(const glm::vec2 location) const
{
	return GetIdx(static_cast<int>(location.y / m_TileSize), static_cast<int>(location.x / m_TileSize));
}


glm::vec2 GameBoardModel::GetOffset(int row, int col) const
{
	return glm::vec2 {col*m_TileSize, row*m_TileSize};
}

TileValue GameBoardModel::GetTileValue(int row, int col) const
{
	return static_cast<TileValue>(m_Grid[GetIdx(row, col)]);
}

TileValue GameBoardModel::GetTileValue(const glm::vec2 location) const
{
	return static_cast<TileValue>(m_Grid[GetIdx(location)]);
}

bool GameBoardModel::IsPlayerAllowedAtLocation(glm::vec2 location) const
{
	return IsTileAtLocationAccessible(location)
	&& IsTileAtLocationAccessible({ location.x + m_TileSize - 1, location.y + m_TileSize - 1 })
	&& IsTileAtLocationAccessible({ location.x , location.y + m_TileSize - 1 })
	&& IsTileAtLocationAccessible({ location.x + m_TileSize - 1, location.y  });
}

bool GameBoardModel::IsTileAtLocationAccessible(glm::vec2 location) const
{
	int row = int(location.y / m_TileSize);
	int col = int(location.x / m_TileSize);
	auto tileValue = m_Grid[GetIdx(row, col)];
	return tileValue != int(TileValue::Wall);
}

glm::vec2 GameBoardModel::GetPlayerSpawnLocation() const
{
	return
	m_PacmanSpawnLocation;
}

glm::vec2 GameBoardModel::GetGhostSpawnLocation(int ghostIdx) const
{
	return  m_GhostSpawnLocations[ghostIdx];
}
