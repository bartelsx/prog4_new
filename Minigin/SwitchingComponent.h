#pragma once
#include "BaseComponent.h"

namespace dae
{
	// This component selects one of its subcomponents when the corresponding Event is received
	class SwitchingComponent :  public BaseComponent, public Observer
    {
	public:
	    ~SwitchingComponent() override = default;
	    SwitchingComponent(const SwitchingComponent& other) = delete;
	    SwitchingComponent(SwitchingComponent&& other) = delete;
	    SwitchingComponent& operator=(const SwitchingComponent& other) = delete;
	    SwitchingComponent& operator=(SwitchingComponent&& other) = delete;

		static std::shared_ptr<SwitchingComponent> Create();
		std::shared_ptr<SwitchingComponent> GetPtr();

		//Set the component that will be selected when receiving an event of eventType
		void Set(TEventType eventType, const std::shared_ptr<BaseComponent> component);

		void HandleEvent(const Event& event) override;

		void Update(float deltaTime) override;
		void Render(bool isDirty) override;

		void SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent) override;

	private:
		SwitchingComponent() = default;
		std::unordered_map<TEventType, std::shared_ptr<BaseComponent>> m_Components{};
		std::shared_ptr<BaseComponent> m_CurrentComponent{};
    };
}
