#pragma once
#include <command.h>

namespace dae
{
	enum GameMode
	{
		SinglePlayer,
		Coop,
		Versus
	};

	class StartGameCommand :
		public Command
	{
	public:
		StartGameCommand(GameMode gameMode);
		~StartGameCommand() override = default;
		StartGameCommand(const StartGameCommand& other) = delete;
		StartGameCommand(StartGameCommand&& other) = delete;
		StartGameCommand& operator=(const StartGameCommand& other) = delete;
		StartGameCommand& operator=(StartGameCommand&& other) = delete;
		void Execute() override;
		void Release() override;
	private:
		GameMode m_GameMode;
	};

	class MainMenuCommand : public Command
	{
	public:
		MainMenuCommand()=default;
		~MainMenuCommand() override = default;
		MainMenuCommand(const MainMenuCommand& other) = delete;
		MainMenuCommand(MainMenuCommand&& other) = delete;
		MainMenuCommand& operator=(const MainMenuCommand& other) = delete;
		MainMenuCommand& operator=(MainMenuCommand&& other) = delete;

		void Execute() override;
		void Release() override {};
	};

	class HallOfFameCommand : public Command
	{
	public:
		HallOfFameCommand() = default;
		~HallOfFameCommand() override = default;
		HallOfFameCommand(const HallOfFameCommand& other) = delete;
		HallOfFameCommand(HallOfFameCommand&& other) = delete;
		HallOfFameCommand& operator=(const HallOfFameCommand& other) = delete;
		HallOfFameCommand& operator=(HallOfFameCommand&& other) = delete;

		void Execute() override;
		void Release() override {};
	};
}

