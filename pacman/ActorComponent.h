#pragma once
#include "BaseComponent.h"
#include "ActorType.h"
#include "EventType.h"
#include "TextureComponent.h"

namespace dae
{
	class ActorComponent : public BaseComponent,  public Observer
	{
	public:
		ActorComponent(ActorType actorType) : m_ActorType(actorType){}
		~ActorComponent() override = default;
		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent& operator=(ActorComponent&& other) = delete;

		ActorType GetType() const { return m_ActorType; }
		void HandleEvent(const Event& event) override;

		void SetSpawnLocation(glm::vec2 spawnLocation);

	protected:
		ActorType m_ActorType{};
		glm::vec2 m_SpawnLocation{};
	};

	inline void ActorComponent::HandleEvent(const Event& event)
	{
		if (event.GetType() == EventType::RESET_LEVEL)
		{
			GetOwner()->SetPosition(m_SpawnLocation);
		}
	}

	inline void ActorComponent::SetSpawnLocation(glm::vec2 spawnLocation)
	{
		m_SpawnLocation = spawnLocation;
		GetOwner()->SetPosition(m_SpawnLocation);
	}
}
