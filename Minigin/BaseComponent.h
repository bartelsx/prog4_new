#pragma once
#include "Transform.h"
#include <memory>

#include "GameObject.h"

namespace dae
{
	class BaseComponent : std::enable_shared_from_this<BaseComponent>
	{
	public:
		BaseComponent() {  }
		virtual ~BaseComponent() {  }
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void Render();
		//void SetTransform(const dae::Transform& transform);
		//void SetPosition(const glm::vec3& pos);

		void SetOwner(const std::shared_ptr<dae::GameObject>& pOwner, bool doAddComponent = true);
		std::shared_ptr<dae::GameObject> GetOwner() const;

	protected:
		dae::Transform m_Transform{};
		bool m_NeedsUpdate{ true };
		std::weak_ptr<dae::GameObject> m_wpOwner;
	};
}

