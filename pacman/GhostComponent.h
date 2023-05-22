#pragma once
#include "ActorComponent.h"

namespace dae
{

	class GhostComponent : public ActorComponent
	{
	public:
		static std::shared_ptr<GhostComponent> Create(std::shared_ptr<Texture2D> pTexture)
		{
			return std::shared_ptr<GhostComponent>(new GhostComponent(pTexture));
		}

	private:
		GhostComponent(std::shared_ptr<Texture2D> pTexture) : ActorComponent(ActorType::Ghost, pTexture){}
		std::shared_ptr<GhostComponent> GetPtr() { return std::dynamic_pointer_cast<GhostComponent>(shared_from_this()); }
	};
}
