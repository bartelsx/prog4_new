#pragma once
#include "SceneManager.h"

namespace dae
{
	struct GridData {
		int width;
		int height;
		std::vector<int> grid;
	};
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		std::vector < std::shared_ptr<GameObject>> GetAllObjects() { return m_objects; };

		void Update(float deltaT);
		void Render() const;
		void LoadLevel(const std::string& path, int w, int h);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		void readJsonFile(const std::string& filename);
		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
		int m_GridSize;
		float m_TileSize = 16;
		
		int m_LevelIndex = 2;
		int m_LevelCount = 3;

		std::vector < std::shared_ptr<GameObject>>  m_pickupsArr;
		std::vector < std::shared_ptr<GameObject>>  m_SpecialPickupsArr;
		std::vector < std::shared_ptr<GameObject>>  m_PowerupsArr;
		std::vector<int> m_Grid;
		int m_Width{};
		int m_Height{};
	};

}
