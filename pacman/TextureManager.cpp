#include "TextureManager.h"

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

	m_Textures[Textures::Background] = rm.LoadTexture("../Data/background.png");
	m_Textures[Textures::Logo] = rm.LoadTexture("../Data/logo.png");
	m_Textures[Textures::Boost] = rm.LoadTexture("../Data/boost.png");
	m_Textures[Textures::Pill] = rm.LoadTexture("../Data/pill.png");
	m_Textures[Textures::Path] = rm.LoadTexture("../Data/path.png");
	m_Textures[Textures::Wall] = rm.LoadTexture("../Data/wall.png");
	m_Textures[Textures::Pacman] = rm.LoadTexture("../Data/pacman.png");
	m_Textures[Textures::MrsPacman] = rm.LoadTexture("../Data/mspacman.png");
	m_Textures[Textures::Ghost1] = rm.LoadTexture("../Data/ghost1.png");
	m_Textures[Textures::Ghost2] = rm.LoadTexture("../Data/ghost2.png");
	m_Textures[Textures::Ghost3] = rm.LoadTexture("../Data/ghost3.png");
	m_Textures[Textures::ScaredGhost] = rm.LoadTexture("../Data/scaredghost.png");

}
