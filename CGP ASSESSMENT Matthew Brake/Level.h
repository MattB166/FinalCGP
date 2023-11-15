#pragma once
#include "SDL.h"
#include "Tank.h"
class Level
{
public:
	Level();
	void PlayGame();
	void NewLevel();
	static void CheckPlayerBounds(Tank* tank);
	static float WorldX;
	static float WorldY;

protected:


	
};

