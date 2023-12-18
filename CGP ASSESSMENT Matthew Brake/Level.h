#pragma once
#include "SDL.h"
#include "Tank.h"
#include "UI_Manager.h"
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
	int LevelNumber = 1;
	int score = 0;
	int PlayerAmmo; 
	int GetLevel();

protected:


	
};

