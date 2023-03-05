#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void TextureComponent::Render(bool) 
{
	auto pos = m_pOwner->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
