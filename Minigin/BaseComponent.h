#pragma once
#include "Transform.h"
#include <memory>

#include "GameObject.h"

namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent() {  }
		virtual ~BaseComponent() {  }
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void Render(bool isDirty);
		//void SetTransform(const dae::Transform& transform);
		//void SetPosition(const glm::vec3& pos);

		void SetOwner(const std::shared_ptr<dae::GameObject> pOwner, bool doAddComponent = true);
		std::shared_ptr<dae::GameObject> GetOwner() { return m_pOwner; };

	protected:
		dae::Transform m_Transform{};
		bool m_NeedsUpdate{ true };
		std::shared_ptr<dae::GameObject> m_pOwner;
	};
}

