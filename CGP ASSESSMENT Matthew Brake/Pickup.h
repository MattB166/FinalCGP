#pragma once
#include "GameObject.h"
class Pickup :public GameObject
{
public:

	Pickup();
	~Pickup();
	Pickup(SDL_Texture* texture);
	void SpawnPickups(int Amount);
	void DrawPickups(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime);

};

