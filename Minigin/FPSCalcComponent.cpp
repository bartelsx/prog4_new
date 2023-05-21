#include "FPSCalcComponent.h"
#include "Font.h"
#include <chrono>

using namespace dae;

void FPSCalcComponent::Update(float deltaTime)
{
	CalcFPS(deltaTime);
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

std::string FPSCalcComponent::GetText()
{
	std::string text{ std::to_string(m_FPS) + " FPS" };
	return text;
}

