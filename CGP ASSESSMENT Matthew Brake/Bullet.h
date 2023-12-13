#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <list>
class Bullet : public GameObject
{
public:
	Bullet();
	void Fire(float TurretAngle, float TurretX, float TurretY);
	void Destroy();
	
private:
	float bullet_Speed = 10;
	RigidBody2D rb;

};

