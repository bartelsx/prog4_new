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

private:
	void ReadJsonFile(const std::string& filename);

	float m_TileSize = 16;
	int m_Width{};
	int m_Height{};
	std::vector<int> m_Grid;
};

