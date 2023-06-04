#pragma once
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		static std::shared_ptr<TextureComponent> Create();
		static std::shared_ptr<TextureComponent> Create(std::shared_ptr<Texture2D> pTexture);

		virtual void Render(bool isDirty) override;

		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);
		virtual std::shared_ptr<Texture2D> GetTexture() { return m_pTexture; }

	protected:
		TextureComponent() {}
		TextureComponent(const std::shared_ptr<Texture2D>& pTexture);

		std::shared_ptr<Texture2D> m_pTexture{};
	};
}

