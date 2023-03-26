#pragma once
#include "Singleton.h"

#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <SDL.h>


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
	class KeyboardInputHandler final : public Singleton<KeyboardInputHandler>
	{
	public:
		KeyboardInputHandler();
		~KeyboardInputHandler() override;
		KeyboardInputHandler(const KeyboardInputHandler& other) = delete;
		KeyboardInputHandler(KeyboardInputHandler&& other) = delete;
		KeyboardInputHandler& operator=(const KeyboardInputHandler& other) = delete;
		KeyboardInputHandler& operator=(KeyboardInputHandler&& other) = delete;

		bool ProcessInput();

		void AddCommand(const SDL_Scancode key, std::shared_ptr<Command>& command);
		void RemoveCommand(const SDL_Scancode key);

	private:
		class KeyboardInputHandlerImpl;
		KeyboardInputHandlerImpl* pKeyboardInputHandlerImpl;
	};

}