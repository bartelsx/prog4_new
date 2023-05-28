#pragma once
#include <command.h>

namespace dae
{
	enum GameModes
	{
		SinglePlayer,
		Coop,
		Versus
	};
	class StartGameCommand :
		public Command
	{
	public:
		StartGameCommand(GameModes gameMode);
		~StartGameCommand() = default;
		StartGameCommand(const StartGameCommand& other) = delete;
		StartGameCommand(StartGameCommand&& other) = delete;
		StartGameCommand& operator=(const StartGameCommand& other) = delete;
		StartGameCommand& operator=(StartGameCommand&& other) = delete;
		void Execute() override;
		void Release() override;
	private:

	};
}

