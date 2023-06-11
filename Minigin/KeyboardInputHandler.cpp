#include <SDL.h>
#include "KeyboardInputHandler.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <thread>
#include <windows.h>
#include <XInput.h>

#include "ControllerInputHandler.h"
#include "command.h"
#include "SoundSystem.h"

using namespace dae;

class KeyboardInputHandler::KeyboardInputHandlerImpl
{
public:
    bool ProcessInput()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT ) {
                return false;
            }
           
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    return false;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                {
                    DoTextInputCommand("\b");
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    DoTextInputCommand("\n");
                }
               
                DoCommandForKey(e.key.keysym.scancode, true);

            }
            if (e.type == SDL_KEYUP)
            {
                DoCommandForKey(e.key.keysym.scancode, false);
            }
            if(e.type == SDL_TEXTINPUT)
            {
                DoTextInputCommand(e.text.text);
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

    void DoTextInputCommand(std::string text)
    {
	    if (m_TextInputCommand != nullptr)
	    {
            m_TextInputCommand->Execute(text);
	    }
    }

 
    void AddCommand(const SDL_Scancode key, const std::shared_ptr<Command>& command)
    {
        m_KeyboardCommands[key] = command;
    }

    void RemoveCommand(const SDL_Scancode key)
    {
        m_KeyboardCommands[key] = nullptr;
    }

    void Clear()
    {
        m_KeyboardCommands.clear();
    }

    void SetTextInputCommand(const std::shared_ptr<TextCommand>& pCommand)
    {
        m_TextInputCommand = pCommand;
    }

private:
    using KeyBoardCommandsMap = std::map<SDL_Scancode, std::shared_ptr<Command>>;
    KeyBoardCommandsMap m_KeyboardCommands{};
    std::shared_ptr<TextCommand> m_TextInputCommand;
};

KeyboardInputHandler::KeyboardInputHandler()
{
    pKeyboardInputHandlerImpl = new KeyboardInputHandlerImpl();
}

KeyboardInputHandler::~KeyboardInputHandler()
{
    delete pKeyboardInputHandlerImpl;
    pKeyboardInputHandlerImpl = nullptr;
}

bool KeyboardInputHandler::ProcessInput() const
{
    return pKeyboardInputHandlerImpl->ProcessInput();
}

void KeyboardInputHandler::AddCommand(const SDL_Scancode key, const std::shared_ptr<Command>& command) const
{
    pKeyboardInputHandlerImpl->AddCommand(key, command);
}
void KeyboardInputHandler::SetTextInputCommand(const std::shared_ptr<TextCommand>& pCommand) const
{
    pKeyboardInputHandlerImpl->SetTextInputCommand(pCommand);
}

void KeyboardInputHandler::RemoveCommand(const SDL_Scancode key) const
{
    pKeyboardInputHandlerImpl->RemoveCommand(key);
}

void KeyboardInputHandler::Clear() const
{
    pKeyboardInputHandlerImpl->Clear();
}


