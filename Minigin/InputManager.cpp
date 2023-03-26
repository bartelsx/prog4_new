#include <SDL.h>
#include "InputManager.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <thread>
#include <windows.h>
#include <XInput.h>


#include "InputManager.h"
#include "SceneManager.h"
#include "ControllerInputHandler.h"
#include "command.h"

bool dae::InputManager::ProcessInput()
{
    //Check keyboard input
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        if (e.type == SDL_KEYDOWN)
        {
            DoCommandForKey(e.key.keysym.scancode, true);

        }
        if (e.type == SDL_KEYUP)
        {
            DoCommandForKey(e.key.keysym.scancode, false);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
        }


    }

    //Check controller input

    ControllerInputHandler::GetInstance().ProcessInput();

    return true;
}

void dae::InputManager::AddCommand(const SDL_Scancode key, std::shared_ptr<Command>& command)
{
    m_KeyboardCommands[key] = command;
}

void dae::InputManager::RemoveCommand(const SDL_Scancode key)
{
    m_KeyboardCommands[key] = nullptr;
}

void dae::InputManager::DoCommandForKey(const SDL_Scancode key, const bool keyPressed)
{
    auto it = m_KeyboardCommands.find(key);
    if (it != m_KeyboardCommands.end())
    {
		auto pCmd = it->second;
	    if (keyPressed)
	    {
            pCmd->Execute();
	    }
        else
        {
            pCmd->Release();
        }
    }
    
}
