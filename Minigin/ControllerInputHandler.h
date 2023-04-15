#pragma once
#include <map>
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "Singleton.h"


class Command;
struct ControllerInput;
enum class ControllerButton;

class ControllerInputHandler : public dae::Singleton<ControllerInputHandler>
{
public:

	~ControllerInputHandler();

	void ProcessInput() const;
	bool IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const;
	bool IsDownThisFrame(const unsigned controllerId, const ControllerButton button) const;
	bool IsUpThisFrame(const unsigned controllerId, const ControllerButton button) const;

	void AddCommand(unsigned id, ControllerButton controllerButton, std::shared_ptr<Command> command) const;
	void RemoveCommand(unsigned int id, const ControllerButton& button) const;
	void RemoveAllCommands() const;

	glm::vec2 GetDirection(const unsigned int controllerId) const;
	float GetSpeed(const unsigned int controllerId) const;
	float GetAcceleration(const unsigned int controllerId) const;

	explicit ControllerInputHandler();

	

private:
	class ControllerInputHandlerImpl;
	std::unique_ptr<ControllerInputHandlerImpl> pControllerImpl;
}; 