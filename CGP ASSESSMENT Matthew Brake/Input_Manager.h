#pragma once
#include "SDL.h"
#include "Tank.h"
class GameManager;
class Input_Manager
{
public:
	static void HandleInput(SDL_Event& sdlEvent, GameManager& gameManager);
};

