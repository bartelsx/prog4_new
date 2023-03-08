#pragma once
#include <memory>
#include "Transform.h"
#include <vector>


namespace dae
{
	class Texture2D;
	class BaseComponent;
	
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime);
		void Render() const;
		dae::Transform GetTransform() const;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		size_t GetComponentCount() const { return m_Components.size(); }
		std::shared_ptr<BaseComponent> GetComponent(int index);
		void RemoveComponent(int index);
		void RemoveComponent(BaseComponent* pComponent);

		void SetPosition(float x, float y);

		std::shared_ptr<GameObject> GetChildAt(int idx) const;
		void SetParent(std::shared_ptr<GameObject> parent);
		std::shared_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const { return m_children.size(); };
		void AddChild(const std::shared_ptr<GameObject> child);

		void UpdateWorldPosition();
		const glm::vec3& GetWorldPosition() ;

	private:
		bool RemoveChild(size_t index);
		void AddChildCore(std::shared_ptr<dae::GameObject> child);
		bool RemoveChildCore(size_t index);
		void SetParentCore(const std::shared_ptr<dae::GameObject>& parent);

		Transform m_transform{};

		std::vector<std::shared_ptr<BaseComponent>> m_Components {};
		std::shared_ptr<GameObject> m_parent{};//weak pointer
		std::vector<std::shared_ptr<GameObject>> m_children{};// can be unique pointers
		bool m_isDirty{true};
		glm::vec3 m_worldPosition{};
		glm::vec3 m_localPosition{};
	};

}
