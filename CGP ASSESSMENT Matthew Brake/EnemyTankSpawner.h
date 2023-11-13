#pragma once
#include <vector>
#include "SDL.h"
#include "BoxCollider.h"


class Tank;
class EnemyTankSpawner ////class for spawning enemy tanks 
{
public:

	EnemyTankSpawner();
	EnemyTankSpawner(SDL_Texture* BaseTexture, SDL_Texture* BarrelTexture);
	~EnemyTankSpawner();
	void SpawnTank(int amountOfTanks);
	void DrawTanks(SDL_Renderer* renderer);
	Tank* getTankByIndex(int index) const;          /// rewrite my own draw function for just tank spawner as too much complexity 
	                                         //using game object and tank one 
	BoxCollider enemyCollider;
	
	void AssignID();
	
	
	


private:

	std::vector<Tank*> spawnedTanks; 
	SDL_Texture* enemyBaseTexture; 
	SDL_Texture* enemyBarrelTexture; 
	SDL_Renderer* renderer;
	float enemy_x;
	float enemy_y; 
	
	int ID; 
};

