#include "GameBoardComponent.h"

#include <fstream>
#include <rapidjson/document.h>

#include "TextureComponent.h"
#include "TextureManager.h"

GameBoardComponent::GameBoardComponent()
{
}

void GameBoardComponent::LoadFromJsonFile(const std::string& path, TextureManager& textureManager)
{
	ReadJsonFile(path);

	for (int col = 0; col < m_Width; ++col)
	{
		for (int row = 0; row < m_Height; ++row)
		{

			float posX = float(col * m_TileSize);
			float posY = float(row * m_TileSize);


			if (m_Grid[m_Width * row + col] != 0)
			{


				const auto wallTextureComp = std::make_shared<TextureComponent>();

				auto object{ dae::GameObject::Create() };
				object->SetPosition(posX, posY);

				switch (m_Grid[m_Width * row + col])
				{
				case 1:
					wallTextureComp->SetTexture(textureManager.GetTexture(Textures::Wall));
					object->AddComponent(wallTextureComp);
					break;
				case 2:
					wallTextureComp->SetTexture(textureManager.GetTexture(Textures::Pill));
					object->AddComponent(wallTextureComp);
					break;
				case 3:
					wallTextureComp->SetTexture(textureManager.GetTexture(Textures::Boost));
					object->AddComponent(wallTextureComp);
					break;
				case 4:
					wallTextureComp->SetTexture(textureManager.GetTexture(Textures::Path));
					object->AddComponent(wallTextureComp);
					break;

				default:
					break;
				}

			 	GetOwner()->AddChild(object);
			}
		}
	}
}

void GameBoardComponent::ReadJsonFile(const std::string& filename)
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
	m_Width = doc["width"].GetInt();
	m_Height = doc["height"].GetInt();
	const rapidjson::Value& grid = doc["grid"];

	// Print the values
	std::cout << "Width: " << m_Width << std::endl;
	std::cout << "Height: " << m_Height << std::endl;
	std::cout << "Grid:" << std::endl;
	for (SizeType i = 0; i < grid.Size(); i++) {
		for (SizeType j = 0; j < grid[i].Size(); j++) {
			std::cout << grid[i][j].GetInt() << " ";
			m_Grid.push_back(grid[i][j].GetInt());
		}
		std::cout << std::endl;
	}
}
