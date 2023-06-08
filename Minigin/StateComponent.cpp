#include "StateComponent.h"

using namespace dae;

std::shared_ptr<StateComponent> StateComponent::Create()
{
	return std::shared_ptr<StateComponent>(new StateComponent());
}

std::shared_ptr<StateComponent> StateComponent::GetPtr()
{
	return std::dynamic_pointer_cast<StateComponent>(shared_from_this());
}

void StateComponent::Set(TEventType eventType, const std::shared_ptr<BaseComponent> component)
{
	if (!m_Components.contains(eventType))
	{
		EventManager::Subscribe(eventType, GetPtr());
	}

	m_Components[eventType] = component;
	component->SetOwner(GetOwner(), false);

	if (m_CurrentComponent == nullptr)
	{
		//First added component will be default component
		m_CurrentComponent = component;
	}
}

void StateComponent::HandleEvent(const Event& event)
{
	const auto* pEventWithOwner = dynamic_cast<const EventWithPayload<std::shared_ptr<GameObject>>*>(&event);

	if (pEventWithOwner == nullptr || pEventWithOwner->GetData() == GetOwner())
	{
		const auto it = m_Components.find(event.GetType());
		if (it != m_Components.end())
		{
			m_CurrentComponent = it->second ;
		}
	}
}

void StateComponent::Update(float deltaTime)
{
	if (m_CurrentComponent != nullptr)
	{
		m_CurrentComponent->Update(deltaTime);
	}
}

void StateComponent::Render(bool isDirty)
{
	if (m_CurrentComponent != nullptr)
	{
		m_CurrentComponent->Render(isDirty);
	}
}

void StateComponent::SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent)
{
	BaseComponent::SetOwner(pOwner, doAddComponent);

	for (auto& pair : m_Components)
	{
		pair.second->SetOwner(pOwner, false);
	}
}
