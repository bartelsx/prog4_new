#include <SDL.h>
#include "KeyboardInputHandler.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <thread>
#include <windows.h>
#include <XInput.h>

#include "ControllerInputHandler.h"
#include "command.h"

class dae::KeyboardInputHandler::KeyboardInputHandlerImpl
{
public:
    bool ProcessInput()
    {
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
        }
        return true;
    }

    void DoCommandForKey(const SDL_Scancode key, const bool keyPressed)
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


    void AddCommand(const SDL_Scancode key, std::shared_ptr<Command>& command)
    {
        m_KeyboardCommands[key] = command;
    }

    void RemoveCommand(const SDL_Scancode key)
    {
        m_KeyboardCommands[key] = nullptr;
    }

private:
    using KeyBoardCommandsMap = std::map<SDL_Scancode, std::shared_ptr<Command>>;
    KeyBoardCommandsMap m_KeyboardCommands{};

};

dae::KeyboardInputHandler::KeyboardInputHandler()
{
    pKeyboardInputHandlerImpl = new KeyboardInputHandlerImpl();
}

dae::KeyboardInputHandler::~KeyboardInputHandler()
{
    delete pKeyboardInputHandlerImpl;
    pKeyboardInputHandlerImpl = nullptr;
}

bool dae::KeyboardInputHandler::ProcessInput()
{
    return pKeyboardInputHandlerImpl->ProcessInput();
}

void dae::KeyboardInputHandler::AddCommand(const SDL_Scancode key, std::shared_ptr<Command>& command)
{
    pKeyboardInputHandlerImpl->AddCommand(key, command);
}

void dae::KeyboardInputHandler::RemoveCommand(const SDL_Scancode key)
{
    pKeyboardInputHandlerImpl->RemoveCommand(key);
}


