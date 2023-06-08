#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FireEventComponent : public BaseComponent
	{
	public:
		~FireEventComponent() override = default;
		FireEventComponent(const FireEventComponent& other) = delete;
		FireEventComponent(FireEventComponent&& other) = delete;
		FireEventComponent& operator=(const FireEventComponent& other) = delete;
		FireEventComponent& operator=(FireEventComponent&& other) = delete;

		static std::shared_ptr<FireEventComponent> Create(TEventType eventType, bool includeOwner);
		void Update(float deltaTime) override;

	private:
		FireEventComponent(TEventType eventType, bool includeOwner);
		TEventType m_EventType;
		bool m_IncludeOwner;
	};
}
