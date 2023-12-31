#pragma once
#include "SDL.h"
#include "Tank.h"
#include "UI_Manager.h"
#include "TimeMaths.h"; 
#include "SDL_ttf.h"
class Level
{
public:
	Level();
	void PlayGame();
	void StartTimer();
	void RenderTimer(float delta, TTF_Font* font, SDL_Renderer* Renderer);
	float GetRemainingTime(); 
	void NewLevel();
	static void CheckPlayerBounds(Tank* tank);
	static bool CheckBulletBounds(Bullet* bullet); 
	static float WorldX;
	static float WorldY;
	int LevelNumber = 1;
	float TimeRemaining = 180.0f; 
	float timeElapsed; 
	bool isTimeRunning; 
	int score = 0;
	int PlayerAmmo; 
	int GetLevel();
	SDL_Texture* timerTexture; 
	SDL_Rect timerRect; 

protected:

	
	
};

