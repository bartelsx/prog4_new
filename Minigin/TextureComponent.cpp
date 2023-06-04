#include "TextureComponent.h"

#include <utility>
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

TextureComponent::TextureComponent(const std::shared_ptr<Texture2D>& pTexture)
{
	SetTexture(pTexture);
}

std::shared_ptr<TextureComponent> TextureComponent::Create()
{
	return std::shared_ptr<TextureComponent>(new TextureComponent());
}

std::shared_ptr<TextureComponent> TextureComponent::Create(std::shared_ptr<Texture2D> pTexture)
{
	return std::shared_ptr<TextureComponent>(new TextureComponent(pTexture));
}

void TextureComponent::Render(bool) 
{
	if (auto pOwner = GetOwner())
	{
		auto pos = pOwner->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*GetTexture(), pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
	assert(m_pTexture != nullptr);
}
