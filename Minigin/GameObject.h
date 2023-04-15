#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

#include "Observer.h"


namespace dae
{
	class Texture2D;
	class BaseComponent;
	
	class GameObject final : public std::enable_shared_from_this<GameObject>, public Subject
	{
	public:
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		static std::shared_ptr<GameObject> Create();

		void Update(float deltaTime);
		void Render() const;
		dae::Transform GetTransform() const;

		void AddComponent(const std::shared_ptr<BaseComponent>& component, bool doSetOwner = true);
		size_t GetComponentCount() const { return m_Components.size(); }
		std::shared_ptr<BaseComponent> GetComponent(int index);
		void RemoveComponent(int index);
		void RemoveComponent(std::shared_ptr<BaseComponent> pComponent);

		void SetPosition(float x, float y);
		void SetPosition(glm::vec2 localPosition);
		glm::vec2 GetPosition() const;

		std::shared_ptr<GameObject> GetChildAt(int idx) const;
		void SetParent(std::shared_ptr<GameObject>& pParent);
		std::shared_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const { return m_children.size(); };
		void AddChild(const std::shared_ptr<GameObject> child);

		void UpdateWorldPosition();
		const glm::vec3& GetWorldPosition() ;


		void Die();
		void PowerUp();
		void FruitPickUp();
		void SmallPickUp();
		void EnemyDead();

	private:
		bool RemoveChild(size_t index);
		GameObject() = default;

		void AddChildCore(std::shared_ptr<dae::GameObject> child);
		bool RemoveChildCore(size_t index);
		void SetParentCore(const std::shared_ptr<dae::GameObject>& parent);

		Transform m_transform{};

		std::vector<std::shared_ptr<BaseComponent>> m_Components {};
		std::weak_ptr<GameObject> m_wpParent{};
		std::vector<std::shared_ptr<GameObject>> m_children{};// can be unique pointers
		bool m_isDirty{true};
		glm::vec3 m_worldPosition{};
		glm::vec3 m_localPosition{};
	};

	
}
