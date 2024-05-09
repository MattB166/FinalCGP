#include "MineBomb.h"

MineBomb::MineBomb()
{

}

MineBomb::MineBomb(SDL_Texture* texture)
{
	m_texture = texture; 
}

void MineBomb::Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	GameObject::Draw(renderer, CameraX, CameraY, MouseX, MouseY, false, deltaTime); 
}

