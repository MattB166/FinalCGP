#pragma once
#include <vector>
#include <list>
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
	void DrawTanks(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime);
	//void DestroyKilledTanks();
	Tank* getTankByIndex(int index) const;          
	void CheckTankSpawnPos(Tank* tank);                                                
	BoxCollider enemyCollider;
	std::vector<Tank*> spawnedTanks;
	std::vector<Tank*> TanksToDestroy;
	void AssignID();
	
	///need a tank movement and shooting function 
	


private:

	
	
	SDL_Texture* enemyBaseTexture; 
	SDL_Texture* enemyBarrelTexture; 
	SDL_Renderer* renderer;
	float enemy_x;
	float enemy_y; 
	
	int ID; 
};

