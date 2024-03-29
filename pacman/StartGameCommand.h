#pragma once
#include <command.h>

namespace dae
{
	class SoundPlayer;
	class GameBoardModel;

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
		StartGameCommand(GameMode gameMode, int level);
		~StartGameCommand() override = default;
		StartGameCommand(const StartGameCommand& other) = delete;
		StartGameCommand(StartGameCommand&& other) = delete;
		StartGameCommand& operator=(const StartGameCommand& other) = delete;
		StartGameCommand& operator=(StartGameCommand&& other) = delete;

		void Execute() override;
		void Release() override;
	private:
		const GameMode m_GameMode;
		int m_Level;
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
		void Release() override {}
	};

	class ToggleMuteCommand : public Command
	{
	public:
		ToggleMuteCommand(const std::shared_ptr<SoundPlayer>& pSoundPlayer);
		~ToggleMuteCommand() override = default;
		ToggleMuteCommand(const ToggleMuteCommand& other) = delete;
		ToggleMuteCommand(ToggleMuteCommand&& other) = delete;
		ToggleMuteCommand& operator=(const ToggleMuteCommand& other) = delete;
		ToggleMuteCommand& operator=(ToggleMuteCommand&& other) = delete;

		void Execute() override;
		void Release() override {}

	private:
		const std::shared_ptr<SoundPlayer> m_pSoundPlayer;
	};

}

