#pragma once
#include "SceneManager.h"


namespace dae
{
	class TextureManager;

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

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
		
		int m_LevelIndex = 2;
		int m_LevelCount = 3;

	};

}
