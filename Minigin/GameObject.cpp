#include <string>
#include "GameObject.h"

#include "BaseComponent.h"
#include "Renderer.h"

using namespace dae;

std::shared_ptr<GameObject> GameObject::Create()
{
	return std::shared_ptr<GameObject>(new GameObject());
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto component : m_Components)
	{
		component->Update(deltaTime);
	}
}


void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component, bool doSetOwner)
{
	//component->SetTransform(m_transform); //initialize the components transform with the transform of the owning gameObject
	if (doSetOwner)
	{
		component->SetOwner(shared_from_this(), false);
	}
	m_Components.push_back(component);
}

std::shared_ptr<BaseComponent> dae::GameObject::GetComponent(int index)
{
	return m_Components[index];
}

void dae::GameObject::RemoveComponent(int index)
{
	if (index >= m_Components.size())
	{
		return;
	}
	const auto lastElement{ m_Components.size() - 1 };
	m_Components[index] = m_Components[lastElement];
	m_Components.pop_back();
}

void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComponent)
{
	std::_Erase_remove_if(m_Components, [pComponent](const std::shared_ptr<BaseComponent>& cmp) {return cmp == pComponent; });
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		
		component->Render();
	}
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
	m_localPosition = { x,y,0 };
	SetDirty(true);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int idx) const
{
	return m_children[idx];
}

void dae::GameObject::SetParentCore(const std::shared_ptr<dae::GameObject>& parent)
{
	m_wpParent = parent;
	SetDirty(true);
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject>& pParent)
{
	auto current = m_wpParent.lock();
	if (current == pParent)
	{
		//already parent
		return;
	}
	if (current)
	{
		for (int idx=0; idx<current->GetChildCount(); ++idx)
		{
			if (current->GetChildAt(idx).get() == this)
			{
				current->RemoveChildCore(idx);
				break;
			}
		}
	}
	SetParentCore(pParent);
	
	pParent->AddChildCore(shared_from_this());
}

void dae::GameObject::AddChildCore(const std::shared_ptr<dae::GameObject> child)
{
	m_children.push_back(child);
	SetDirty(true);
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject> child)
{
	auto oldParent = child->GetParent();
	if (oldParent != nullptr)
	{
		for (int idx = 0; idx < oldParent->GetChildCount(); ++idx)
		{
			if (oldParent->GetChildAt(idx).get() == child.get())
			{
				oldParent->RemoveChildCore(idx);
				break;
			}
		}
	}
	child->SetParentCore(shared_from_this());
	AddChildCore(child);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_wpParent.lock();
}


bool dae::GameObject::RemoveChildCore(size_t index)
{
	m_children.erase(m_children.begin() + index);
	SetDirty(true);
	return true;
}

bool dae::GameObject::RemoveChild(size_t index)
{
	if (index < m_children.size())
	{
		m_children[index]->SetParentCore(nullptr);
		return RemoveChildCore(index);
 	}

	return false;
}

const glm::vec3& GameObject::GetWorldPosition() 
{
	if (m_isDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

void GameObject::SetDirty(const bool newValue)
{
	if (newValue == m_isDirty)
	{
		return;
	}
	m_isDirty = newValue;
	if (newValue)
	{
		//when m_isDirty is set to true, it should ripple through to all children
		for(const auto& child : m_children)
		{
			child->SetDirty(newValue);
		}
	}
}

void GameObject::UpdateWorldPosition()
{
	if (m_isDirty)
	{
		auto pParent = m_wpParent.lock();
		if (pParent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = pParent->GetWorldPosition() + m_localPosition;
	}
	SetDirty(false);
}
