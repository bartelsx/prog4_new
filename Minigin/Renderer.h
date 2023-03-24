#pragma once
#include <SDL.h>
#include <vector>

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};

		bool m_ShowDemo{ true };
		std::vector<float> m_TrashCashData{};
		int m_TrashCashSize{};
		int m_TrashCashSteps{};
		std::vector<float> m_TrashCashDataObject3D{};
		std::vector<float> m_TrashCashDataObject3DAlt{};
		int m_TrashCashDataSizeObject3D{};
		int m_TrashCashDataSizeObject3DAlt{};
		int m_TrashCashStepsObject3D{};

		void DrawGUI();
		void DrawPlotForTranshCash();
		void DrawPlotForGameObject3D();

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

