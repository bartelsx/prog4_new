#include "EllipticalMoveComponent.h"

#include <SDL_stdinc.h>

void dae::EllipticalMoveComponent::Update(float deltaTime)
{
	BaseComponent::Update(deltaTime);
	m_time += deltaTime;
	if (const auto pOwner = GetOwner())
	{
		float angle = m_time / m_period * 2.f * float(M_PI) + m_startAngle;
		float x = m_center.x + m_radiusX * cosf(angle);
		float y = m_center.y + m_radiusY * sinf(angle);
		pOwner->SetPosition(x, y);
	}
}
