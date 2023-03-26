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
            std::cout << "down\n";

        }
        if (e.type == SDL_KEYUP)
        {
            
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
        }


    }

    //Check controller input

    ControllerInputHandler::GetInstance().ProcessInput();

    return true;
}

// old
//bool dae::InputManager::ProcessInput()
//{
//    XINPUT_STATE currentState{};
//    int controllerIndex{};
//
//    ZeroMemory(&currentState, sizeof(XINPUT_STATE));
//    XInputGetState(controllerIndex, &currentState);
//
//    SDL_Event e;
//    while (SDL_PollEvent(&e))
//    {
//        if (e.type == SDL_QUIT)
//        {
//            return false;
//        }
//        if (e.type == SDL_KEYDOWN)
//        {
//
//        }
//        if (e.type == SDL_MOUSEBUTTONDOWN)
//        {
//
//        }
//      
//        // etc...
//    }
// 
//
//    
//    if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
//    {
//        std::cout << "B\n";
//    }
//	if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
//    {
//        std::cout << "X\n";
//    }
//	if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
//    {
//        std::cout << "A\n";
//    }
//    if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
//    {
//        std::cout << "Y\n";
//    }
//
//    if (currentState.Gamepad.sThumbLY & XINPUT_GAMEPAD_B)
//    {
//
//        auto t = std::chrono::high_resolution_clock::now();
//        std::cout << "\rsThumbLX: " << currentState.Gamepad.sThumbLX << " - sThumbRX: " << currentState.Gamepad.sThumbRX;
//       
//       
//
//       std::cout<< currentState.dwPacketNumber<< std::endl;
//        float LX = currentState.Gamepad.sThumbLX;
//        float LY = currentState.Gamepad.sThumbLY;
//
//        //determine how far the controller is pushed
//        float magnitude = sqrt(LX * LX + LY * LY);
//
//        //determine the direction the controller is pushed
//       // float normalizedLX = LX / magnitude;
//       // float normalizedLY = LY / magnitude;
//        std::cout << " Y " << LY << std::endl;
//        float normalizedMagnitude = 0;
//
//        //check if the controller is outside a circular dead zone
//        if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//        {
//            //clip the magnitude at its expected maximum value
//            if (magnitude > 32767) magnitude = 32767;
//
//            //adjust magnitude relative to the end of the dead zone
//            magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
//
//            //optionally normalize the magnitude with respect to its expected range
//            //giving a magnitude value of 0.0 to 1.0
//            normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
//           //
//           // std::cout << "normalizedMagnitude " << normalizedMagnitude;
//
//        }
//        else //if the controller is in the deadzone zero out the magnitude
//        {
//            magnitude = 0.0;
//            normalizedMagnitude = 0.0;
//    		std::cout << "the controller is in the deadzone zero out the magnitude\n";
//        }
//        auto t2 = std::chrono::high_resolution_clock::now() - t;
//        t += std::chrono::milliseconds(16) - t2; // we want ~60 fps
//        std::this_thread::sleep_until(t);
//    }
//	if (currentState.Gamepad.sThumbLX & XINPUT_GAMEPAD_LEFT_THUMB)
//    {
//        //std::cout << "jjj\n";
//    }
//
//    if (currentState.Gamepad.sThumbLX & XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//    {
//        //std::cout << "dead\n";
//    }
//
//
//    return true;
//}