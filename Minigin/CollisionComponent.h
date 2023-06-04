#pragma once
#include "BaseComponent.h"

namespace dae
{
	class CollisionComponent : public BaseComponent
	{
	public:
		~CollisionComponent() override = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		static std::shared_ptr<CollisionComponent> Create(TEventType eventToFire, bool publishOwner, bool publishOtherOwner, float tolerance);

		void AddWatchedObject(std::shared_ptr<GameObject> watchedObject);

		void Update(float deltaTime) override;

	private:
		CollisionComponent(TEventType eventToFire, bool publishOwner, bool publishOtherOwner, float tolerance);
		void Publish(std::shared_ptr<GameObject> otherOwner) const;

		TEventType m_EventToFire;
		bool m_PublishOwner;
		bool m_PublishOtherOwner;
		float m_Tolerance;

		bool m_wasColliding{};

		std::vector<std::shared_ptr<GameObject>> m_WatchedObjects;
	};
}
