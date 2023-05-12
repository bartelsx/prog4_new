#include "Scene.h"

#include <fstream>
#include <sstream>

#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <iterator>
#include <memory>
#include <utility>

#include "TextureComponent.h"
#include "rapidjson/document.h"
using namespace rapidjson;
using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaT)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaT);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::LoadLevel(const std::string& path,int w,int h)
{
	readJsonFile(path);

	int offsetX = int((w - m_Width * m_TileSize)/2);
	int offsetY = int((h - m_Height * m_TileSize)/2);

	for (int col = 0; col < m_Width; ++col)
	{
		for (int row = 0; row < m_Height; ++row)
		{

			float posX = float(col * m_TileSize)+offsetX;
			float posY = float(row * m_TileSize)+offsetY;
			

			if (m_Grid[m_Width*row+col] != 0)
			{


				const auto wallTextureComp = std::make_shared<TextureComponent>();

				auto object{ dae::GameObject::Create() };
				object->SetPosition(posX, posY);

				switch (m_Grid[m_Width * row + col])
				{
				case 1:
					wallTextureComp->SetTexture("../Data/wall.png");
					object->AddComponent(wallTextureComp);
					break;
				case 2:
					wallTextureComp->SetTexture("../Data/pill.png");
					m_pickupsArr.push_back(object);
					object->AddComponent(wallTextureComp);
					break;
				case 3:
					wallTextureComp->SetTexture("../Data/boost.png");
					m_PowerupsArr.push_back(object);
					object->AddComponent(wallTextureComp);
					break;
				case 4:
					wallTextureComp->SetTexture("../Data/path.png");
					m_SpecialPickupsArr.push_back(object);
					object->AddComponent(wallTextureComp);
					break;

				default:
					break;
				}



				Add(object);
			}
		}
	}
}

void dae::Scene::readJsonFile(const std::string& filename) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	// Read the entire file into a string
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	Document doc;
	if (doc.Parse(str.c_str()).HasParseError()) {
		std::cerr << "Failed to parse JSON" << std::endl;
		return;
	}

	// Get the values from the document
	m_Width = doc["width"].GetInt();
	m_Height = doc["height"].GetInt();
	const Value& grid = doc["grid"];

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