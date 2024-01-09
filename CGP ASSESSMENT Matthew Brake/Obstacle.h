#pragma once
#include "GameObject.h"
#include "EnemyTankSpawner.h"
#include "Tank.h"
#include <cstdlib>
#include <ctime>
#include <vector>
class Obstacle :public GameObject
{
public:
	Obstacle();
	~Obstacle();
	Obstacle(SDL_Texture* texture);
	void SpawnObstacles(int Amount, const EnemyTankSpawner& tankSpawner);
	void DrawObstacles(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime);
	void DestroyObstacles(); 
	void SetPosition(int x, int y); 
	void SetColliderPos(int x, int y);
	bool contains(int px, int py) const;
	const std::vector<Obstacle*>& GetSpawnedObstacles() const; 
	std::vector<Obstacle*> SpawnedObstacles; 
	std::vector<Obstacle*> ObstaclesToDestroy; 
	static const std::vector<int> Rotations; 
	
private:
	
	

};

