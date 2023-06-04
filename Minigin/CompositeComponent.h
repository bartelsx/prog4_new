#pragma once
#include "BaseComponent.h"

namespace dae
{
	class CompositeComponent : public BaseComponent
	{
	public:
		~CompositeComponent() override = default;
		CompositeComponent(const CompositeComponent& other) = delete;
		CompositeComponent(CompositeComponent&& other) = delete;
		CompositeComponent& operator=(const CompositeComponent& other) = delete;
		CompositeComponent& operator=(CompositeComponent&& other) = delete;

		static std::shared_ptr<CompositeComponent> Create();

		void Add(const std::shared_ptr<BaseComponent> component);

		void Update(float deltaTime) override;
		void Render(bool isDirty) override;

		void SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent) override;

	private:
		CompositeComponent();

		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	};
}

