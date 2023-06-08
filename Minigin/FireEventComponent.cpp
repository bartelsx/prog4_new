#include "FireEventComponent.h"

using namespace dae;


std::shared_ptr<FireEventComponent> FireEventComponent::Create(TEventType eventType, bool includeOwner)
{
	return std::shared_ptr<FireEventComponent>(new FireEventComponent(eventType, includeOwner));
}

void FireEventComponent::Update(float )
{
	if (m_IncludeOwner)
	{
		EventManager::Publish(m_EventType, GetOwner());
	}
	else
	{
		EventManager::Publish(m_EventType);
	}
}

FireEventComponent::FireEventComponent(TEventType eventType, bool includeOwner)
	:	m_EventType(eventType)
	,	m_IncludeOwner(includeOwner)
{}
