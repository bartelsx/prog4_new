#include "GameBoardComponent.h"

#include <fstream>
#include <rapidjson/document.h>

#include "BaseComponent.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "TextureManager.h"

using namespace dae;


GameBoardComponent::GameBoardComponent(const std::shared_ptr<GameBoardModel>& pModel, const std::shared_ptr<TextureManager>& pTextureManager) : m_pModel(pModel)
{
	m_pTextures[0] = pTextureManager->GetTexture(Textures::WallTexture);
	m_pTextures[1] = pTextureManager->GetTexture(Textures::PillTexture);
	m_pTextures[2] = pTextureManager->GetTexture(Textures::BoostTexture);
	m_pTextures[3] = pTextureManager->GetTexture(Textures::PathTexture);
}

void GameBoardComponent::Render(bool )
{
	glm::vec3 upperLeft{};
	if (auto pOwner = GetOwner())
	{
		upperLeft = pOwner->GetWorldPosition();
	}


	for (int row = 0; row < m_pModel->GetRows(); ++row)
	{
		for (int col = 0; col < m_pModel->GetColumns(); ++col)
		{
			TileValue tileValue = m_pModel->GetTileValue(col, row);
			glm::vec2 offset = m_pModel->GetOffset(col, row);
			int textureIdx = (tileValue == TileValue::Gate ? 4 : static_cast<int>(tileValue)) - 1;
			dae::Renderer::GetInstance().RenderTexture(*m_pTextures[textureIdx], upperLeft.x+offset.x, upperLeft.y+offset.y);
		}
	}
}
