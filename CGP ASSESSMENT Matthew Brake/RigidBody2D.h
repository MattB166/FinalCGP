#pragma once
#include "Vector2.h"


class RigidBody2D 
{
public:
	Vector2 velocity; 
	float mass; 
	
	float angle;
	float angularVelocity;
	float angularDrag; 
	float torque;
	
	RigidBody2D();



	//void AddForce(Vector2 force);
	//void ApplyTorque(float Appliedtorque);
	//void Rotate(float RotationAngle);
	//void update(float deltaTime);
};

