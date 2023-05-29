#include "TimerComponent.h"

using namespace dae;

TimerComponent::TimerComponent(TEventType triggerEvent, TEventType timedEvent, float delay)
	: m_TriggerEvent(triggerEvent)
	, m_TimedEvent(timedEvent)
	, m_Delay(delay)
{
}

void TimerComponent::HandleEvent(const Event& event)
{
	if (event.Is(m_TriggerEvent))
	{
		m_CountDown += m_Delay;
	}
}

void TimerComponent::Update(float deltaTime)
{
	if (m_CountDown > 0.f)
	{
		m_CountDown = std::max(0.f, m_CountDown - deltaTime);

		if (m_CountDown <= 0.f)
		{
			EventManager::Publish(m_TimedEvent);
		}
	}
}

