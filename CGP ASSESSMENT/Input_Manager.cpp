#include "Input_Manager.h"
#include <cstdlib> 

const Uint8* Input_Manager::m_keyStates = nullptr;
const Uint8* Input_Manager::m_previousKeyStates = nullptr; 

void Input_Manager::Init()
{
	m_keyStates = SDL_GetKeyboardState(NULL);
	m_previousKeyStates = (Uint8*)std::malloc(SDL_NUM_SCANCODES);
	SDL_memcpy((void*)m_previousKeyStates, m_keyStates, SDL_NUM_SCANCODES);
}

bool Input_Manager::GetKey(SDL_Scancode key)
{
	return m_keyStates[key];
}

bool Input_Manager::GetKeyDown(SDL_Scancode key)
{
	return m_keyStates[key] && !(m_previousKeyStates[key]);
}

bool Input_Manager::GetKeyUp(SDL_Scancode key)
{
	return !(m_keyStates[key]) && m_previousKeyStates[key];
}

void Input_Manager::UpdateKeyStates()
{
	SDL_memcpy((void*)m_previousKeyStates, m_keyStates, SDL_NUM_SCANCODES);
}
