#include "CompositeComponent.h"

using namespace dae;

std::shared_ptr<CompositeComponent> CompositeComponent::Create()
{
	return std::shared_ptr<CompositeComponent>(new CompositeComponent());
}

void CompositeComponent::Add(const std::shared_ptr<BaseComponent> component)
{
	m_Components.emplace_back(component);
	component->SetOwner(GetOwner(), false);
}

void CompositeComponent::Update(float deltaTime)
{
	for (auto pComp : m_Components)
	{
		pComp->Update(deltaTime);
	}
}

void CompositeComponent::Render(bool isDirty)
{
	for (auto pComp : m_Components)
	{
		pComp->Render(isDirty);
	}
}

void CompositeComponent::SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent)
{
	BaseComponent::SetOwner(pOwner, doAddComponent);

	for (auto& pComp : m_Components)
	{
		pComp->SetOwner(pOwner, false);
	}
}

CompositeComponent::CompositeComponent()
	: m_Components{}
{}
