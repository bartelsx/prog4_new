#include "BaseComponent.h"

using namespace dae;

void BaseComponent::Update(float )
{
}

void BaseComponent::Render(bool ) 
{
}

void BaseComponent::SetTransform(const dae::Transform& transform)
{
	m_Transform = transform;
}

void BaseComponent::SetPosition(const glm::vec3& pos)
{

	m_Transform.SetPosition(pos.x, pos.y, pos.z);
}

//void BaseComponent::SetOwner(std::shared_ptr<dae::GameObject> pOwner)
//{
//	//assert(pOwner);
//	//if ( ! pOwner)
//	//{
//	//	return;
//	//}
//	//if (m_pOwner)
//	//{
//	//	m_pOwner->RemoveComponent(this);
//	//}
//	//m_pOwner = pOwner;
//	//m_pOwner->AddComponent(this);
//}
