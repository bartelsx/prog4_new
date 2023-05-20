#pragma once
#include "TextureComponent.h"

namespace dae
{

	class PacmanComponent :	public TextureComponent
	{
	public:
		PacmanComponent(const std::shared_ptr<dae::Texture2D>& pTexture);
		~PacmanComponent() = default;
		PacmanComponent(const PacmanComponent& other) = delete;
		PacmanComponent(PacmanComponent&& other) = delete;
		PacmanComponent& operator=(const PacmanComponent& other) = delete;
		PacmanComponent& operator=(PacmanComponent&& other) = delete;

		void Update(float deltaTime) override;

	};
}

