#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Tank.h"
#include "EnemyTankSpawner.h"
#include "Collision.h"
#include "Bullet.h"
#include "Input_Manager.h"
#include "TimeMaths.h"
#include "SDL_ttf.h"
#include "Level.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
class Input_Manager;
class GameManager
{
public: 
	GameManager(SDL_Renderer* renderer, TTF_Font* font);
	~GameManager();
	void HandleInput(SDL_Event& sdlEvent);
	bool Initialise();
	void LoadAssets();
	void Render();
	void Cleanup();
	void RunGame();
	Tank& GetPlayerTank();
	int MouseX = 0;
	int MouseY = 0;
	Mix_Chunk* coinsSFX;
	SDL_Texture* TankTexture;
	SDL_Texture* BarrelTexture;
	SDL_Texture* EnemyTankTexture;
	SDL_Texture* enemyBarrelTexture;
	SDL_Texture* BulletTexture;
	Mix_Music* music;
	bool keeprunning;
	float deltaTime;
private:
	SDL_Renderer* g_sdlRenderer;
	SDL_Window* g_sdlWindow;
	TTF_Font* g_font;
	Tank PlayerTank;
	EnemyTankSpawner* enemyTanks;
    Input_Manager InputManager;
	Level GameLevel;
	float g_cameraX = 0;
	float g_cameraY = 0;
	
	 
	SDL_Texture* LoadTexture(const char* filename);
	
	
	
};

