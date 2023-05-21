#pragma once


#include <xstring>

#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class FPSCalcComponent : public BaseComponent, public TextProvider
	{

	public:
		FPSCalcComponent() {  };
		std::string GetText() override;
		void Update(float deltaTime) override;

	private:
		int m_FPS{};
		void CalcFPS(float deltaTime);
		float m_WaitTime{};


		const float TimeBetweenUpdates{0.5};
	};
}

