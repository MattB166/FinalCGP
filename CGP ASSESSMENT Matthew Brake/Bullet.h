#pragma once
#include "SDL.h"
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	void Fire();
	void Destroy();
	void Ricochet();
private:
	float bullet_Speed = 10;

};

