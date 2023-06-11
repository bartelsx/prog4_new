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

	m_Textures[Textures::BackgroundTexture] = rm.LoadTexture("background.png");
	m_Textures[Textures::LogoTexture] = rm.LoadTexture("logo.png");
	m_Textures[Textures::BoostTexture] = rm.LoadTexture("boost.png");
	m_Textures[Textures::PillTexture] = rm.LoadTexture("pill.png");
	m_Textures[Textures::PathTexture] = rm.LoadTexture("path.png");
	m_Textures[Textures::WallTexture] = rm.LoadTexture("wall.png");
	m_Textures[Textures::PacmanTexture] = rm.LoadTexture("pacman.png");
	m_Textures[Textures::MrsPacmanTexture] = rm.LoadTexture("mspacman.png");
	m_Textures[Textures::BlinkyTexture] = rm.LoadTexture("ghost1.png");
	m_Textures[Textures::InkyTexture] = rm.LoadTexture("ghost2.png");
	m_Textures[Textures::ClydeTexture] = rm.LoadTexture("ghost3.png");
	m_Textures[Textures::PinkyTexture] = rm.LoadTexture("ghost-pink.png");
	m_Textures[Textures::ScaredGhostTexture] = rm.LoadTexture("scaredghost.png");
	m_Textures[Textures::EyesTexture] = rm.LoadTexture("eyes.png");
	m_Textures[Textures::FruitTexture] = rm.LoadTexture("fruit.png");

}
