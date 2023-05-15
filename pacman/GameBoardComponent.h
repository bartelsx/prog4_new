#pragma once
#include "BaseComponent.h"
#include "rapidjson/document.h"

class TextureManager;

class GameBoardComponent : public dae::BaseComponent
{
public:
	GameBoardComponent();
	~GameBoardComponent() override = default;
	int GetWidth() { return int(m_Width * m_TileSize); };
	int GetHeight() { return int(m_Height * m_TileSize); };
	GameBoardComponent(const GameBoardComponent& other) = delete;
	GameBoardComponent(GameBoardComponent&& other) = delete;
	GameBoardComponent& operator=(const GameBoardComponent& other) = delete;
	GameBoardComponent& operator=(GameBoardComponent&& other) = delete;
	void LoadFromJsonFile(const std::string& path, TextureManager& textureManager);
	glm::vec2 GetPlayerLocation();
	glm::vec2 GetGhost1Location();
	glm::vec2 GetGhost2Location();
	glm::vec2 GetGhost3Location();
private:
	void ReadJsonFile(const std::string& filename);

	std::vector<glm::vec2> ghostsPos{};
	glm::vec2 locPacman{};
	float m_TileSize = 16;
	int m_Width{};
	int m_Height{};
	std::vector<int> m_Grid;
};

