#include "CollisionComponent.h"

using namespace dae;


CollisionComponent::CollisionComponent(TEventType eventToFire, bool publishOwner, bool publishOtherOwner, float tolerance)
	: m_EventToFire(eventToFire)
	, m_PublishOwner(publishOwner)
	, m_PublishOtherOwner(publishOtherOwner)
	, m_Tolerance(tolerance)
{}

std::shared_ptr<CollisionComponent> CollisionComponent::Create(TEventType eventToFire, bool publishOwner, bool publishOtherOwner, float tolerance)
{
	return std::shared_ptr<CollisionComponent>(new CollisionComponent(eventToFire, publishOwner, publishOtherOwner, tolerance));
}

void CollisionComponent::AddWatchedObject(std::shared_ptr<GameObject> watchedObject)
{
	m_WatchedObjects.emplace_back(watchedObject);
}

void CollisionComponent::Update(float deltaTime)
{
	BaseComponent::Update(deltaTime);
	const auto myPosition = GetOwner()->GetPosition();

	for (const auto& pObj : m_WatchedObjects)
	{
		const auto otherPosition = pObj->GetPosition();
		const float distance = std::abs(myPosition.x - otherPosition.x) + std::abs(myPosition.y - otherPosition.y);

		if (distance <= m_Tolerance)
		{
			if (!m_wasColliding)
			{
				Publish(pObj);
				m_wasColliding = true;
			}
		}
		else
		{
			m_wasColliding = false;
		}
	}
}

void CollisionComponent::Publish(std::shared_ptr<GameObject> otherOwner) const
{
	if (m_PublishOwner && m_PublishOtherOwner)
	{
		EventManager::Publish(m_EventToFire, std::make_pair(GetOwner(), otherOwner));
	}
	else if (m_PublishOtherOwner)
	{
		EventManager::Publish(m_EventToFire, otherOwner);
	}
	else if (m_PublishOwner)
	{
		EventManager::Publish(m_EventToFire, GetOwner());
	}
	else
	{
		EventManager::Publish(m_EventToFire);
	}
}
