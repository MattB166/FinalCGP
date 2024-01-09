#pragma once
#include "SDL.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(SDL_Texture* texture);
	void Fire(float TurretAngle, float TurretX, float TurretY);
	void Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime) override; ///trying to draw bullet 
	void Destroy();
	
	
private:
	float bullet_Speed = 10;
	float damage; 
	RigidBody2D rb;

};

