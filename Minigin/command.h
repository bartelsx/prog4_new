#pragma once
#include "GameObject.h"

namespace dae
{

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
}