#include "TimerComponent.h"

using namespace dae;


TimerComponent::TimerComponent(float interval, TEventType eventType)
	: m_Interval(interval)
	, m_EventType(eventType)
{
	m_RemainingTime = interval;
}

std::shared_ptr<TimerComponent> TimerComponent::Create(float interval, TEventType eventType)
{
	return std::shared_ptr<TimerComponent>(new TimerComponent(interval, eventType));
}

void TimerComponent::Update(float deltaTime)
{
	m_RemainingTime -= deltaTime;

	if (m_RemainingTime <= 0)
	{
		EventManager::Publish(m_EventType, GetOwner());
		m_RemainingTime = m_Interval;
	}
}

