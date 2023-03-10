#include "BaseComponent.h"

using namespace dae;

void BaseComponent::Update(float )
{
}

void BaseComponent::Render() 
{
}

//void BaseComponent::SetTransform(const dae::Transform& transform)
//{
//	m_Transform = transform;
//}
//
//void BaseComponent::SetPosition(const glm::vec3& pos)
//{
//
//	m_Transform.SetPosition(pos.x, pos.y, pos.z);
//}

void BaseComponent::SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent)
{
	const auto current = GetOwner();
	if (current == pOwner)
	{
		return;
	}
	if (current)
	{
		current->RemoveComponent(shared_from_this());
	}
	m_wpOwner = pOwner;
	if (doAddComponent)
	{
		pOwner->AddComponent(shared_from_this(), false);
	}
}

std::shared_ptr<dae::GameObject> BaseComponent::GetOwner() const
{
	return m_wpOwner.lock();
}
