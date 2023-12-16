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
	static bool CheckBulletBounds(Bullet* bullet); 
	static float WorldX;
	static float WorldY;
	int LevelNumber = 0;
	int GetLevel();

protected:


	
};

