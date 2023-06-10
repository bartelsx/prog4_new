#pragma once
#include <SDL_pixels.h>
#include <xstring>

#include "BaseComponent.h"
#include "EventType.h"

namespace dae
{
	class Font;
	class HallOfFameModel;

	class HighScoresComponent :public BaseComponent, public Observer
	{
	public:
		~HighScoresComponent() override = default;
		HighScoresComponent(const HighScoresComponent& other) = delete;
		HighScoresComponent(HighScoresComponent&& other) = delete;
		HighScoresComponent& operator=(const HighScoresComponent& other) = delete;
		HighScoresComponent& operator=(HighScoresComponent&& other) = delete;

		static std::shared_ptr<HighScoresComponent> Create(const std::shared_ptr<HallOfFameModel>& pHallOfFameModel, const std::shared_ptr<Font>& pFont);
		void AddTexture(const float x, const float y, const std::string& text);

		void Render(bool isDirty) override;
		void HandleEvent(const Event& event) override;

	private:
		HighScoresComponent(const std::shared_ptr<HallOfFameModel>& pHallOfFameModel, const std::shared_ptr<Font>& pFont);
		const std::shared_ptr<HallOfFameModel> m_pHallOfFameModel;
		const std::shared_ptr<Font> m_pFont;

		std::vector < std::pair<glm::vec2, std::unique_ptr<Texture2D>>> m_Textures{};
		bool m_IsDirty{ true };
		SDL_Color m_Color{ 255,255,255 };
	};

	inline void HighScoresComponent::HandleEvent(const Event& event)
	{
		if (event.Is(EventType::HIGHSCORES_CHANGED))
		{
			m_IsDirty = true;
		}
	}
}
