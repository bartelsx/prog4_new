#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void TextureComponent::Render(bool) 
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
