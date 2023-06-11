#pragma once
#include <SDL_ttf.h>


#include "TextComponent.h"

namespace dae
{
	
	class TextProcessor
	{
	public:
		virtual void Process(std::string text) = 0;
	};

	class TextHandler
	{
	public:
		virtual void HandleText(std::string& string) = 0;
	};

	class EditBoxComponent : public TextComponent, public TextHandler
	{
	public:
		EditBoxComponent(std::shared_ptr<Font>& font, std::shared_ptr<TextProcessor> pTextProcessor )
			: TextComponent(m_text, font)
			,m_pTextProcessor(pTextProcessor)
		{

		}

		void HandleText(std::string& string) override
		{
			if (string == "\b")
			{
				m_text.pop_back();
			}
			else if(string == "\n")
			{
				m_pTextProcessor->Process(m_text);
				return;
			}
			else
			{
				m_text += string;
			}
				m_isDirty = true;
		}

		void Update(float ) override
		{
			if (!m_IsStarted)
			{
				SDL_StartTextInput();
				m_IsStarted = true;
			}
		}

	private:
		bool m_IsStarted{};
		std::shared_ptr<TextProcessor> m_pTextProcessor;
	};
}

