#pragma once
#include "BaseComponent.h"


namespace dae
{
	class TimerComponent : public BaseComponent
	{
	public:
		~TimerComponent() override = default;
		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		static std::shared_ptr<TimerComponent> Create(float interval, TEventType eventType);

		void Update(float deltaTime) override;

	private:
		TimerComponent(float interval, TEventType eventType);

		float m_RemainingTime;
		float m_Interval;
		TEventType m_EventType;
	};
}
