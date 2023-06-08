#pragma once
#include "BaseComponent.h"

namespace dae
{
	// Immediately go to the specified position (without taking a speed/direction into account)
	class GoToComponent : public BaseComponent
	{
	public:
		~GoToComponent() override = default;
		GoToComponent(const GoToComponent& other) = delete;
		GoToComponent(GoToComponent&& other) = delete;
		GoToComponent& operator=(const GoToComponent& other) = delete;
		GoToComponent& operator=(GoToComponent&& other) = delete;

		static std::shared_ptr<GoToComponent> Create(glm::vec2 position);
		void Update(float deltaTime) override;

	private:
		GoToComponent(glm::vec2 position);
		glm::vec2 m_Position;
	};
}
