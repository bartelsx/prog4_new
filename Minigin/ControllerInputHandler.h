#pragma once
#include <map>
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "Singleton.h"

namespace dae
{
	class Command;
	struct ControllerInput;
	enum class ControllerButton;


	class ControllerInputHandler : public Singleton<ControllerInputHandler>
	{
	public:

		~ControllerInputHandler() override;

		void ProcessInput() const;
		bool IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const;
		bool IsDownThisFrame(const unsigned controllerId, const ControllerButton button) const;
		bool IsUpThisFrame(const unsigned controllerId, const ControllerButton button) const;

		void AddCommand(unsigned id, ControllerButton controllerButton, std::shared_ptr<Command> command) const;
		void RemoveCommand(unsigned int id, const ControllerButton& button) const;
		void Clear() const;

		glm::vec2 GetDirection(const unsigned int controllerId) const;
		float GetSpeed(const unsigned int controllerId) const;
		float GetAcceleration(const unsigned int controllerId) const;

		explicit ControllerInputHandler();

		//when 2 controllers are connected,they seem to not always have id's 0 and 1
		int GetControllerID(int controllerNumber); 

		int GetNumberOfControllers(); 

	private:
		class ControllerInputHandlerImpl;
		std::unique_ptr<ControllerInputHandlerImpl> pControllerImpl;
		
	};
}