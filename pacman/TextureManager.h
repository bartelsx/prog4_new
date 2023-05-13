#pragma once
#include <map>

#include "ResourceManager.h"

enum Textures
{
	Wall, Pill, Boost, Pacman, MrsPacman, Ghost1, Ghost2, Ghost3, ScaredGhost, Background, Logo, Path	
};

class TextureManager
{
public:
	TextureManager();
	~TextureManager() = default;
	TextureManager(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;

	std::shared_ptr<dae::Texture2D> GetTexture(Textures id);

private:
	void LoadTextures();
	std::map<Textures, std::shared_ptr<dae::Texture2D>> m_Textures;
	
};


