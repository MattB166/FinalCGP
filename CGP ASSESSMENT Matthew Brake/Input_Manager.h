#pragma once
#include "SDL.h"
class Input_Manager
{
public:
	static void Init();

	static bool GetKey(SDL_Scancode key);
	static bool GetKeyDown(SDL_Scancode key);
	static bool GetKeyUp(SDL_Scancode key);

	static void UpdateKeyStates();
	

private:
	static const Uint8* m_keyStates;
	static const Uint8* m_previousKeyStates;
};

