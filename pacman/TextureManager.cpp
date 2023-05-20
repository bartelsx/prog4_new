#include "TextureManager.h"
using namespace dae;

TextureManager::TextureManager()
{
	LoadTextures();
}

std::shared_ptr<dae::Texture2D> TextureManager::GetTexture(Textures id)
{
	return m_Textures[id];
}

void TextureManager::LoadTextures()
{
	auto& rm = dae::ResourceManager::GetInstance();

	m_Textures[Textures::BackgroundTexture] = rm.LoadTexture("../Data/background.png");
	m_Textures[Textures::LogoTexture] = rm.LoadTexture("../Data/logo.png");
	m_Textures[Textures::BoostTexture] = rm.LoadTexture("../Data/boost.png");
	m_Textures[Textures::PillTexture] = rm.LoadTexture("../Data/pill.png");
	m_Textures[Textures::PathTexture] = rm.LoadTexture("../Data/path.png");
	m_Textures[Textures::WallTexture] = rm.LoadTexture("../Data/wall.png");
	m_Textures[Textures::PacmanTexture] = rm.LoadTexture("../Data/pacman.png");
	m_Textures[Textures::MrsPacmanTexture] = rm.LoadTexture("../Data/mspacman.png");
	m_Textures[Textures::Ghost1Texture] = rm.LoadTexture("../Data/ghost1.png");
	m_Textures[Textures::Ghost2Texture] = rm.LoadTexture("../Data/ghost2.png");
	m_Textures[Textures::Ghost3Texture] = rm.LoadTexture("../Data/ghost3.png");
	m_Textures[Textures::ScaredGhostTexture] = rm.LoadTexture("../Data/scaredghost.png");

}
