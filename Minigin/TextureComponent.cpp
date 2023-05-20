#include "TextureComponent.h"

#include <utility>
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

TextureComponent::TextureComponent(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	SetTexture(pTexture);
}

void TextureComponent::Render(bool) 
{
	if (auto pOwner = GetOwner())
	{
		auto pos = pOwner->GetWorldPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	m_pTexture = pTexture;
	assert(m_pTexture != nullptr);
}
