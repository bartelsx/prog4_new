#include "FPSCalcComponent.h"


#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"

#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <chrono>

using namespace dae;

void FPSCalcComponent::Update(float deltaTime)
{

	CalcFPS(deltaTime);

	/*if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,0 };
		std::string text{ std::to_string(m_FPS) + " FPS" };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<dae::Texture2D>(texture);

		m_NeedsUpdate = false;
	}*/


}

void FPSCalcComponent::CalcFPS(float deltaTime)
{
	m_WaitTime += deltaTime;
	if (m_WaitTime >= TimeBetweenUpdates)
	{
		m_WaitTime = 0;
		auto fps = 1.f / deltaTime;
		m_FPS = int(fps);
		m_NeedsUpdate = true;
	}

}

void FPSCalcComponent::Notify(Event& event, Subject*)
{
	if (event.m_type == EventType::ACTOR_DIED)
	{
		//std::cout << "dead \n";
	}
}

std::string FPSCalcComponent::GetText()
{
	std::string text{ std::to_string(m_FPS) + " FPS" };
	return text;
}

