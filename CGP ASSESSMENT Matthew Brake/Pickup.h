#pragma once
#include "GameObject.h"
#include "EnemyTankSpawner.h"
#include "Obstacle.h"
#include <vector>
#include <cstdlib>
class Pickup :public GameObject
{
public:

	Pickup();
	~Pickup();
	Pickup(SDL_Texture* texture, SDL_Texture* PickedUpTexture);
	void SpawnPickups(int Amount, const EnemyTankSpawner& tankSpawner, const Obstacle& obstacle);
	void SetPosition(int x, int y); 
	void SetColliderPos(int x, int y);
	int GetValue();
	void PickupItem();
	void DrawPickups(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime);
	std::vector<Pickup*> spawnedPickups; 
	bool isPickedup; 
	SDL_Texture* SecondTexture; 
private:

	float value; 

};

