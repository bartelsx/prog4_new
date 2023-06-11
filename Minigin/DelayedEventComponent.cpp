#include "DelayedEventComponent.h"

using namespace dae;

DelayedEventComponent::DelayedEventComponent(TEventType triggerEvent, TEventType timedEvent, float delay)
	: m_TriggerEvent(triggerEvent)
	, m_TimedEvent(timedEvent)
	, m_Delay(delay)
{
}

void DelayedEventComponent::HandleEvent(const Event& event)
{
	if (event.Is(m_TriggerEvent))
	{
		m_CountDown += m_Delay;

		m_pEventToPublish = std::shared_ptr<Event>(event.Clone());
		m_pEventToPublish->SetType(m_TimedEvent);
	}
}

void DelayedEventComponent::Update(float deltaTime)
{
	if (m_CountDown > 0.f)
	{
		m_CountDown = std::max(0.f, m_CountDown - deltaTime);

		if (m_CountDown <= 0.f)
		{
			EventManager::Publish(m_pEventToPublish);
		}
	}
}

