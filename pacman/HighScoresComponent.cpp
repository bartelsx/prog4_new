#include "HighScoresComponent.h"
#include "Font.h"
#include "HallOfFameModel.h"
#include "PathFinder.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

std::shared_ptr<HighScoresComponent> HighScoresComponent::Create(const std::shared_ptr<HallOfFameModel>& pHallOfFameModel, const std::shared_ptr<Font>& pFont)
{
	auto ptr = std::shared_ptr<HighScoresComponent>(new HighScoresComponent(pHallOfFameModel, pFont));
	EventManager::Subscribe(EventType::HIGHSCORES_CHANGED, ptr);
	return ptr;
}

void HighScoresComponent::AddTexture(const float x, const float y, const std::string& text)
{

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), m_Color);
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
	m_Textures.emplace_back(std::pair(glm::vec2{ x, y }, std::make_unique<Texture2D>(texture)));
}

void HighScoresComponent::Render(bool isDirty)
{
	const auto& itemsToDisplay = m_pHallOfFameModel->GetData();

	if (itemsToDisplay.empty())
	{
		return;
	}

	auto lineSpacing{ 32.f };
	auto locXName{ 0.f }, locXScore{ 530.f }, locY{ 0.f };

	isDirty |= m_IsDirty;
	if (isDirty)
	{
		m_Textures.clear();

		for (auto& entry : itemsToDisplay)
		{
			AddTexture(locXName, locY, entry->Name);
			AddTexture(locXScore, locY, std::to_string(entry->Score));
			locY += lineSpacing;
		}
		m_IsDirty = false;
	}

	auto pOwner = GetOwner();

	if (pOwner)
	{
		const auto& pos = pOwner->GetWorldPosition();
		for (auto& element : m_Textures)
		{
			if (element.second)
			{
				Renderer::GetInstance().RenderTexture(*element.second, pos.x + element.first.x, pos.y + element.first.y);
			}
		}
	}
}

HighScoresComponent::HighScoresComponent(const std::shared_ptr<HallOfFameModel>& pHallOfFameModel, const std::shared_ptr<Font>& pFont)
	: m_pHallOfFameModel(pHallOfFameModel)
	, m_pFont(pFont)
{
}
