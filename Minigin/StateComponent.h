#pragma once
#include "BaseComponent.h"

namespace dae
{
	// This component selects one of its subcomponents when the corresponding Event is received
	class StateComponent :  public BaseComponent, public Observer
    {
	public:
	    ~StateComponent() override = default;
	    StateComponent(const StateComponent& other) = delete;
	    StateComponent(StateComponent&& other) = delete;
	    StateComponent& operator=(const StateComponent& other) = delete;
	    StateComponent& operator=(StateComponent&& other) = delete;

		static std::shared_ptr<StateComponent> Create();
		std::shared_ptr<StateComponent> GetPtr();

		//Set the component that will be selected when receiving an event of eventType
		void Set(TEventType eventType, const std::shared_ptr<BaseComponent> component);

		void HandleEvent(const Event& event) override;

		void Update(float deltaTime) override;
		void Render(bool isDirty) override;

		void SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent) override;

	private:
		StateComponent() = default;
		std::unordered_map<TEventType,  std::shared_ptr<BaseComponent>> m_Components{};
		std::shared_ptr<BaseComponent> m_CurrentComponent{};
    };
}
