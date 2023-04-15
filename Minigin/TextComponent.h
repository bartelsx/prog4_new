#pragma once
#include <string>
#include <memory>
#include "SDL_pixels.h"
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class BaseComponent;
	class TextProvider;

	class TextProvider
	{
	public:
		virtual std::string GetText() = 0;

		TextProvider() {}
		virtual ~TextProvider() = default;
		TextProvider(const TextProvider& other) = delete;
		TextProvider(TextProvider&& other) = delete;
		TextProvider& operator=(const TextProvider& other) = delete;
		TextProvider& operator=(TextProvider&& other) = delete;
	};

	template <typename T>
	class LambdaTextProvider : public TextProvider
	{
	public:
		LambdaTextProvider(const T& owner, std::string(*pgetTextFunc)(T)) :m_pGetTextFunc{ pgetTextFunc }, m_owner(owner) {  }
		static std::shared_ptr<LambdaTextProvider<T>> Create(const T& owner, std::string(*pGetTextFunc)(T))
		{
			return std::make_shared <LambdaTextProvider<T>>(owner, pGetTextFunc());
		}

		std::string GetText() override
		{
			return m_pGetTextFunc(m_owner);
		}

	private:
		std::string(*m_pGetTextFunc)(T);
		T m_owner;
	};


	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		TextComponent(const  std::shared_ptr<TextProvider> textProvider, std::shared_ptr<Font> font);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render(bool isDirty) override;

		void SetText(const std::string& text);
		void SetTextProvider(const  std::shared_ptr<TextProvider> textProvider);
		void SetColor(SDL_Color color);

	private:
		bool m_isDirty;
		std::string m_text;
		std::shared_ptr<TextProvider> m_textProvider{ nullptr };
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_color{ 255,255,255 };

	};

}

