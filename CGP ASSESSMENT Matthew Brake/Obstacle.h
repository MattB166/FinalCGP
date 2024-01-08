#pragma once
#include "GameObject.h"
class Obstacle :public GameObject
{
public:
	void SpawnObstacles(int Amount);
	void DrawObstacles(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, float deltaTime);
};

