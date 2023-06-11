#pragma once
#include "BaseComponent.h"
#include "command.h"

namespace dae
{
	class TriggerComponent : public BaseComponent, public Observer
	{
	public:
		~TriggerComponent() override = default;
		TriggerComponent(const TriggerComponent& other) = delete;
		TriggerComponent(TriggerComponent&& other) = delete;
		TriggerComponent& operator=(const TriggerComponent& other) = delete;
		TriggerComponent& operator=(TriggerComponent&& other) = delete;

		static std::shared_ptr<TriggerComponent> Create(TEventType eventType, const std::shared_ptr<Command>& pCommand);

		void HandleEvent(const Event& event) override;

	private:
		TriggerComponent(TEventType eventType, const std::shared_ptr<Command>& pCommand);
		TEventType m_EventType;
		const std::shared_ptr<Command> m_pCommand;
	};
}
