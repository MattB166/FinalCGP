#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y; 
}


float Vector2::GetX() const
{
	return x;
}

float Vector2::GetY() const
{
	return y; 
}

void Vector2::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::Normalize()
{
	float mag = GetMagnitude();
	return { x / mag, y / mag };
}

float Vector2::GetMagnitude()
{
	return sqrt(x * x + y * y);
}
