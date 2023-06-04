#pragma once
#include <map>

#include "ResourceManager.h"

namespace dae
{

	enum Textures
	{
		WallTexture, PillTexture, BoostTexture, PacmanTexture, MrsPacmanTexture, BlinkyTexture, InkyTexture, ClydeTexture, PinkyTexture, ScaredGhostTexture, EyesTexture, BackgroundTexture, LogoTexture, PathTexture
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
}