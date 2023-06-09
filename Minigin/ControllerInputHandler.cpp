

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

#include "ControllerInputHandler.h"

#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include "command.h"
#include "KeyboardInputHandler.h"

using namespace dae;
class ControllerInputHandler::ControllerInputHandlerImpl
{
	using ControllerKey = std::pair<unsigned, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;
	ControllerCommandsMap m_ControllerCommands{};
	XINPUT_STATE* m_CurrentState{};
	XINPUT_STATE* m_PreviousState{};
	int* m_ButtonChanges;



	glm::vec2* m_Directions;
	float* m_Speed;
	float* m_Acceleration;

public:
	std::vector<int> m_ControllerIds{};
	ControllerInputHandlerImpl()
		:m_CurrentState(new XINPUT_STATE[XUSER_MAX_COUNT]), m_PreviousState(new XINPUT_STATE[XUSER_MAX_COUNT])
	{
		
		Init();
		m_ButtonChanges = new int[XUSER_MAX_COUNT];
		m_Directions = new glm::vec2[XUSER_MAX_COUNT];
		m_Speed = new float[XUSER_MAX_COUNT];
		m_Acceleration = new float[XUSER_MAX_COUNT];
		ZeroMemory(m_PreviousState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		ZeroMemory(m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	}

	~ControllerInputHandlerImpl()
	{
		delete[] m_CurrentState;
		m_CurrentState = nullptr;

		delete[] m_PreviousState;
		m_PreviousState = nullptr;

		delete[] m_ButtonChanges;
		m_ButtonChanges = nullptr;

		delete[] m_Directions;
		m_Directions = nullptr;

		delete[] m_Speed;
		m_Speed = nullptr;

		delete[] m_Acceleration;
		m_Acceleration = nullptr;
	}
	void Init()
	{
		SDL_Init(SDL_INIT_JOYSTICK);
		int numControllers = SDL_NumJoysticks();
		for (int i = 0; i < numControllers; ++i) {
			SDL_Joystick* joystick = SDL_JoystickOpen(i);
			SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
			joystickID;

			m_ControllerIds.emplace_back(joystickID);
			SDL_JoystickClose(joystick);
		}
	}
	void ReadThumb(unsigned int controllerId, XINPUT_STATE& state)
	{
		//std::cout << state.dwPacketNumber << std::endl;
		short LX = state.Gamepad.sThumbLX;
		short LY = state.Gamepad.sThumbLY;
		if (LX == m_PreviousState[controllerId].Gamepad.sThumbLX && LY == m_PreviousState[controllerId].Gamepad.sThumbLY)
		{
			return;
		}
		//determine how far the controller is pushed
		float magnitude = sqrtf(float(LX) * LX + LY * LY);

		//determine the direction the controller is pushed
		float normalizedLX = LX / magnitude;
		float normalizedLY = LY / magnitude;
		auto direction = glm::vec2{ normalizedLX,normalizedLY };

		//std::cout << " Y " << LY << std::endl;
		float normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			//clip the magnitude at its expected maximum value
			if (magnitude > 32767) magnitude = 32767;

			//adjust magnitude relative to the end of the dead zone
			magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			//optionally normalize the magnitude with respect to its expected range
			//giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			//

			m_Directions[controllerId] = direction;
			m_Speed[controllerId] = normalizedMagnitude;
			m_Acceleration[controllerId] = 0;
		}
		else
		{
			m_Directions[controllerId] = glm::vec2{ 0,0 };
			m_Speed[controllerId] = 0;
			m_Acceleration[controllerId] = 0;
		}

	}

	void ProcessInput()
	{
		ReadState();


		for (auto& b : m_ControllerCommands)
		{
			auto controllerId = b.first.first;
			auto button = b.first.second;
			auto command = b.second;

			if (button < ControllerButton::LeftJoystick)
			{
				if (IsDownThisFrame(controllerId, button))
				{
					command->Execute();
				}
				if (IsUpThisFrame(controllerId, button))
				{
					command->Release();
				}
			}
			if (button == ControllerButton::LeftJoystick && IsLeftThumbChanged(controllerId)
				|| button == ControllerButton::RightJoystick && IsRightThumbChanged(controllerId))
			{
				command->Execute();
			}

		}
	}

	void ReadState()
	{
		std::swap(m_PreviousState, m_CurrentState);

		for (DWORD i{}; i < XUSER_MAX_COUNT; ++i)
		{
			XInputGetState(i, &m_CurrentState[i]);
			m_ButtonChanges[i] = m_CurrentState[i].Gamepad.wButtons ^ m_PreviousState[i].Gamepad.wButtons;
			ReadThumb(i, m_CurrentState[i]);
		}
	}

	bool IsDownThisFrame(const unsigned controllerId, const ControllerButton button) const
	{

		int down = m_ButtonChanges[controllerId] & m_CurrentState[controllerId].Gamepad.wButtons;
		return down & static_cast<unsigned int>(button);
	}

	bool IsUpThisFrame(const unsigned controllerId, const ControllerButton button) const
	{
		int up = m_ButtonChanges[controllerId] & ~(m_CurrentState[controllerId].Gamepad.wButtons);
		return up & static_cast<unsigned int>(button);
	}

	bool IsInDeadZoneLeft(const XINPUT_STATE& state) const
	{
		return abs(state.Gamepad.sThumbLX) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && abs(state.Gamepad.sThumbLY) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}

	bool IsInDeadZoneRight(const XINPUT_STATE& state) const
	{
		return abs(state.Gamepad.sThumbRX) <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abs(state.Gamepad.sThumbRY) <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	}

	bool DeadZoneLeftChangedThisFrame(const unsigned int controllerId) const
	{
		return IsInDeadZoneLeft(m_CurrentState[controllerId]) ^ IsInDeadZoneLeft(m_PreviousState[controllerId]);
	}

	bool DeadZoneRightChangedThisFrame(const unsigned int controllerId) const
	{
		return IsInDeadZoneRight(m_CurrentState[controllerId]) ^ IsInDeadZoneRight(m_PreviousState[controllerId]);
	}

	bool IsLeftThumbChanged(unsigned int controllerId) const
	{
		return DeadZoneLeftChangedThisFrame(controllerId)
			|| (!IsInDeadZoneLeft(m_CurrentState[controllerId])
				&& (m_CurrentState[controllerId].Gamepad.sThumbLX != m_PreviousState[controllerId].Gamepad.sThumbLX || m_CurrentState[controllerId].Gamepad.sThumbLY != m_PreviousState[controllerId].Gamepad.sThumbLY)
				);
	}

	bool IsRightThumbChanged(unsigned int controllerId) const
	{
		return DeadZoneLeftChangedThisFrame(controllerId)
			|| (!IsInDeadZoneRight(m_CurrentState[controllerId])
				&& (m_CurrentState[controllerId].Gamepad.sThumbRX != m_PreviousState[controllerId].Gamepad.sThumbRX || m_CurrentState[controllerId].Gamepad.sThumbRY != m_PreviousState[controllerId].Gamepad.sThumbRY)
				);
	}

	bool IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const
	{
		return m_CurrentState[controllerButton.first].Gamepad.wButtons & static_cast<unsigned int>(controllerButton.second);
	}

	void AddCommand(unsigned int id, const ControllerButton controllerButton, std::shared_ptr<Command> command)
	{


		m_ControllerCommands[std::make_pair(id, controllerButton)] = command;

	}

	void RemoveCommand(unsigned int id, const ControllerButton& button)
	{
		m_ControllerCommands[std::make_pair(id, button)] = nullptr;
	}

	void RemoveCommands()
	{
		m_ControllerCommands.clear();
	}

	glm::vec2 GetDirection(const unsigned contollerId) const
	{
		return m_Directions[contollerId];
	}

	float GetSpeed(const unsigned conrollerId) const
	{
		return m_Speed[conrollerId];
	}

	float GetAcceleration(const unsigned controllerId) const
	{
		return m_Acceleration[controllerId];
	}

};

void ControllerInputHandler::ProcessInput() const
{
	pControllerImpl->ProcessInput();
}

bool ControllerInputHandler::IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const
{
	return pControllerImpl->IsPressed(controllerButton);
}

bool ControllerInputHandler::IsDownThisFrame(const unsigned controllerId, const ControllerButton button) const
{
	return pControllerImpl->IsDownThisFrame(controllerId, button);
}

bool ControllerInputHandler::IsUpThisFrame(const unsigned controllerId, const ControllerButton button) const
{
	return pControllerImpl->IsUpThisFrame(controllerId, button);
}

void ControllerInputHandler::AddCommand(unsigned id, ControllerButton controllerButton, std::shared_ptr<Command> command) const
{
	pControllerImpl->AddCommand(id, controllerButton, command);
}

void ControllerInputHandler::RemoveCommand(unsigned int id, const ControllerButton& button) const
{
	pControllerImpl->RemoveCommand(id, button);
}

void ControllerInputHandler::RemoveAllCommands() const
{
	pControllerImpl->RemoveCommands();
}

glm::vec2 ControllerInputHandler::GetDirection(const unsigned controllerId) const
{
	return pControllerImpl->GetDirection(controllerId);
}

float ControllerInputHandler::GetSpeed(const unsigned controllerId) const
{
	return pControllerImpl->GetSpeed(controllerId);
}

float ControllerInputHandler::GetAcceleration(const unsigned controllerId) const
{
	return pControllerImpl->GetAcceleration(controllerId);
}

ControllerInputHandler::ControllerInputHandler()
{
	pControllerImpl = std::make_unique<ControllerInputHandlerImpl>();
}

int ControllerInputHandler::GetControllerID(int controllerNumber)
{
	return pControllerImpl->m_ControllerIds[controllerNumber];
}

int ControllerInputHandler::GetNumberOfControllers()
{
	return static_cast<int>(pControllerImpl->m_ControllerIds.size());
}

ControllerInputHandler::~ControllerInputHandler()
{

}
