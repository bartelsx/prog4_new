#pragma once
#include "Singleton.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

#include <map>
#include <memory>
#include <SDL.h>
#include <vector>


class Command;
class ControllerInputHandler;

struct ControllerInput
{
	unsigned int id;
	bool pressed;
};

enum class ControllerButton
{
	DpadUp = 0x0001,
	DpadDown = 0x0002,
	DpadLeft = 0x0004,
	DpadRight = 0x0008,
	Start = 0x0010,
	Back = 0x0020,
	LeftThumb = 0x0040,
	RightThumb = 0x0080,
	LeftShoulder = 0x0100,
	RightShoulder = 0x0200,
	ButtonA = 0x1000,
	ButtonB = 0x2002,
	ButtonX = 0x4000,
	ButtonY = 0x8000,
	LeftJoystick = 0xC000,
	RightJoystick = 0xC001,
};

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();

		void AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id);
		void AddCommand(const std::map<SDL_Scancode, std::shared_ptr<Command>>& inputCommands, unsigned int id);
		void RemoveCommand(const ControllerButton& button, unsigned int id);
		void ResetCommands();
		InputManager(){}

	private:

		using KeyBoardKey = std::pair<unsigned, SDL_Scancode>;
		using KeyBoardCommandsMap = std::map<KeyBoardKey, std::shared_ptr<Command>>;
		KeyBoardCommandsMap m_KeyboardCommands{};

		using ControllerBoardKey = std::pair<unsigned, ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerBoardKey, std::shared_ptr<Command>>;
		ControllerCommandsMap m_ControllerCommands{};
	};

}