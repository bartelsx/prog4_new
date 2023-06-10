#pragma once
#include "GameObject.h"
#include <string>

#include "../pacman/EditBoxComponent.h"

namespace dae
{
	class TextHandler;

	class Command
	{
	public:
		explicit Command()
		{}
		virtual ~Command() {}
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
		virtual void Release() = 0;

	protected:
		dae::GameObject* GetGameObject() const { return m_pGameObject; };
	private:
		dae::GameObject* m_pGameObject = nullptr;
	};

	template <typename T>
	class CommandWithOwner : public Command
	{
	public:
		CommandWithOwner(std::shared_ptr<T> pOwner) : m_pOwner(pOwner) {}
		CommandWithOwner(const CommandWithOwner& other) = delete;
		CommandWithOwner(CommandWithOwner&& other) = delete;
		CommandWithOwner& operator=(const CommandWithOwner& other) = delete;
		CommandWithOwner& operator=(CommandWithOwner&& other) = delete;

		std::shared_ptr<T> GetOwner() const { return m_pOwner; }

	protected:
		std::shared_ptr<T> m_pOwner;
	};

	class GameObjectCommand : public CommandWithOwner<dae::GameObject>
	{};



	class TextCommand
	{
	public:
		TextCommand(std::shared_ptr<TextHandler> pTextHandler)
		  : m_pTextHandler(pTextHandler)
		{}

		~TextCommand() = default;
		TextCommand(const TextCommand& other) = delete;
		TextCommand(TextCommand&& other) = delete;
		TextCommand& operator=(const TextCommand& other) = delete;
		TextCommand& operator=(TextCommand&& other) = delete;

		void Execute(std::string& text)
		{
			if (m_pTextHandler != nullptr)
			{
				m_pTextHandler->HandleText(text);
			}
		}

	private:
		std::shared_ptr<TextHandler> m_pTextHandler;
	};

};