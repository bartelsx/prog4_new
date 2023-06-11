#include "TriggerComponent.h"

using namespace dae;

std::shared_ptr<TriggerComponent> TriggerComponent::Create(TEventType eventType, const std::shared_ptr<Command>& pCommand)
{
	std::shared_ptr<TriggerComponent> ptr(new TriggerComponent(eventType, pCommand));

	EventManager::Subscribe(eventType, ptr);

	return ptr;
}

void TriggerComponent::HandleEvent(const Event& event)
{
	if (event.Is(m_EventType))
	{
		m_pCommand->Execute();
	}
}

TriggerComponent::TriggerComponent(TEventType eventType, const std::shared_ptr<Command>& pCommand)
	: m_EventType(eventType)
	, m_pCommand(pCommand)
{}
