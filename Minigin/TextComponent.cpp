#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	: m_font(std::move(font)), m_textTexture(nullptr)
{
	SetText(text);
}

dae::TextComponent::TextComponent(const std::shared_ptr<TextProvider> textProvider, std::shared_ptr<Font> font)
	: m_font(std::move(font)), m_textTexture(nullptr)
{
	SetTextProvider(textProvider);
}

void dae::TextComponent::Update(float)
{
	if (m_textProvider != nullptr)
	{
		auto newText = m_textProvider.get()->GetText();
		if (newText != m_text)
		{
			SetText( newText);
		}
	}
}

void dae::TextComponent::Render()
{
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_textTexture = std::make_shared<Texture2D>(texture);

	auto pOwner = GetOwner();

	if (m_textTexture != nullptr && pOwner)
	{
		const auto& pos = pOwner->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
}

void dae::TextComponent::SetTextProvider(const std::shared_ptr<TextProvider> textProvider)
{
	m_textProvider = textProvider;
}

void dae::TextComponent::SetColor(SDL_Color color)
{
	m_color = color;
}


