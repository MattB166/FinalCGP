#pragma once
#include "BoxCollider.h"

class Collision
{
public:

	static bool CircleCollision(float c1X, float c1Y, float r1, float c2X, float c2Y, float r2);   //useful for bullets. simple circle collision
	// possibly use aabb for square/rectangular collision. does not support rotations 
	//SAT for tank collision 
	
	static bool SquareCollision(BoxCollider collider1, BoxCollider collider2);  //aabb example for basic box collision.
	// if both axis overlap the boxes overlap
	


private:

	

};

