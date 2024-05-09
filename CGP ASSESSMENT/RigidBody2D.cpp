#include "RigidBody2D.h"

RigidBody2D::RigidBody2D()
{
	velocity = Vector2();
	mass = 1.0f;
	angle = 0.0f;
	angularDrag = 0.0f;
	angularVelocity = 0.0f;
	torque = 0.0f; 
}

//void RigidBody2D::AddForce(Vector2 force)
//{
//}

/*void RigidBody2D::ApplyTorque(float Appliedtorque)
{
	torque += Appliedtorque;
}*/

//void RigidBody2D::Rotate(float RotationAngle)
//{
//	
//}

//void RigidBody2D::update(float deltaTime)
//{
//
//}
