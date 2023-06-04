#pragma once
#include "BaseComponent.h"
#include "Events.h"

namespace dae
{
	/**
	 * This component will wait for a triggerEvent, and then fire a delayedEvent some time later
	 */
	class TimerComponent : public BaseComponent, public Observer
	{
	public:
		~TimerComponent() override = default;
		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		static std::shared_ptr<TimerComponent> Create(TEventType triggerEvent, TEventType timedEvent, float delay)
		{
			auto ptr = std::shared_ptr<TimerComponent>(new TimerComponent(triggerEvent, timedEvent, delay));
			EventManager::Subscribe(triggerEvent, ptr);
			return ptr;
		}

		void HandleEvent(const Event& event) override;
		void Update(float deltaTime) override;

	private:
		TimerComponent(TEventType triggerEvent, TEventType timedEvent, float delay);

		TEventType m_TriggerEvent;
		TEventType m_TimedEvent;
		float m_Delay;
		float m_CountDown{};
		std::unique_ptr<Event> m_pEventToPublish{};
	};
}
