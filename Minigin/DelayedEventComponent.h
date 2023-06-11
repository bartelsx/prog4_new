#pragma once
#include "BaseComponent.h"
#include "Events.h"

namespace dae
{
	/**
	 * This component will wait for a triggerEvent, and then fire a delayedEvent some time later
	 */
	class DelayedEventComponent : public BaseComponent, public Observer
	{
	public:
		~DelayedEventComponent() override = default;
		DelayedEventComponent(const DelayedEventComponent& other) = delete;
		DelayedEventComponent(DelayedEventComponent&& other) = delete;
		DelayedEventComponent& operator=(const DelayedEventComponent& other) = delete;
		DelayedEventComponent& operator=(DelayedEventComponent&& other) = delete;

		static std::shared_ptr<DelayedEventComponent> Create(TEventType triggerEvent, TEventType timedEvent, float delay)
		{
			auto ptr = std::shared_ptr<DelayedEventComponent>(new DelayedEventComponent(triggerEvent, timedEvent, delay));
			EventManager::Subscribe(triggerEvent, ptr);
			return ptr;
		}

		void HandleEvent(const Event& event) override;
		void Update(float deltaTime) override;

	private:
		DelayedEventComponent(TEventType triggerEvent, TEventType timedEvent, float delay);

		TEventType m_TriggerEvent;
		TEventType m_TimedEvent;
		float m_Delay;
		float m_CountDown{};
		std::shared_ptr<Event> m_pEventToPublish{};
	};
}
