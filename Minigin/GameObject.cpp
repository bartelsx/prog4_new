#include <string>
#include "GameObject.h"

#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto component : m_Components)
	{
		component->Update(deltaTime);
	}
}


void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	component->SetTransform(m_transform); //initialize the components transform with the transform of the owning gameObject
	m_Components.push_back(component);
}

std::shared_ptr<BaseComponent> dae::GameObject::GetComponent(int index)
{
	return m_Components[index];
}

void dae::GameObject::RemoveComponent(int index)
{
	const auto lastElement{ m_Components.size() - 1 };
	m_Components[index] = m_Components[lastElement];
	m_Components.pop_back();
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component->Render(false);
	}

	
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int idx) const
{
	return m_children[idx];
}

void dae::GameObject::SetParentCore(const std::shared_ptr<dae::GameObject>& parent)
{
	m_parent = parent;
	m_isDirty = true;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	if (m_parent != nullptr)
	{
		for (int idx=0; idx<m_parent->GetChildCount(); ++idx)
		{
			if (m_parent->GetChildAt(idx).get() == this)
			{
				m_parent->RemoveChildCore(idx);
				break;
			}
		}
	}
	SetParentCore(parent);
	parent->AddChildCore(std::shared_ptr<GameObject>(this));
}

void dae::GameObject::AddChildCore(const std::shared_ptr<dae::GameObject> child)
{
	m_children.push_back(child);
	m_isDirty = true;
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
	child->SetParentCore(std::shared_ptr<GameObject>(this));
	AddChildCore(child);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_parent;
}


bool dae::GameObject::RemoveChildCore(size_t index)
{
	m_children.erase(m_children.begin() + index);
	m_isDirty = true;
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
