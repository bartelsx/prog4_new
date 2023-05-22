#pragma once
#include "BaseComponent.h"
#include "ActorType.h"
#include "TextureComponent.h"

namespace dae
{
	class ActorComponent : public TextureComponent
	{
	public:
		ActorComponent(ActorType actorType, const std::shared_ptr<Texture2D>& pTexture) : TextureComponent(pTexture), m_ActorType(actorType){}
		~ActorComponent() override = default;
		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent& operator=(ActorComponent&& other) = delete;

		ActorType GetType() const { return m_ActorType; }
		glm::vec2 GetPosition() const { return GetOwner()->GetPosition(); }

	protected:
		ActorType m_ActorType{};
	};
}
