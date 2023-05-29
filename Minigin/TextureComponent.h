#pragma once
#include <string>
#include "Texture2D.h"
#include "BaseComponent.h"
class TextureComponent :   public dae::BaseComponent
{
public:
	TextureComponent(){}
	TextureComponent(const std::shared_ptr<dae::Texture2D>& pTexture);

	//virtual void Update(float deltaTime) override;
	virtual void Render(bool isDirty) override;


	void SetTexture(const std::shared_ptr<dae::Texture2D>& pTexture);

	//virtual ~TextureComponent();

protected:
	virtual std::shared_ptr<dae::Texture2D> GetTexture() { return m_pTexture; }
	std::shared_ptr<dae::Texture2D> m_pTexture{};
};

