#pragma once
#include "SDL.h"
#include "GameObject.h"
class MineBomb : public GameObject
{
public:
	MineBomb();
	MineBomb(SDL_Texture* texture);
	void Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime) override;
private:
	float damage; 
};

