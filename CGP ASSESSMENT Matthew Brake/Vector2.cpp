#include "Vector2.h"
#include <cmath>

 const Vector2 Vector2::Down(0, -1);
 const Vector2 Vector2::Left(-1, 0);
 const Vector2 Vector2::Right(1, 0);
 const Vector2 Vector2::Up(0, 1); 
 const Vector2 Vector2::Zero(0, 0); 
	 

 Vector2 Vector2::operator+(const Vector2& other) const
 {
	 return Vector2(x + other.x, y + other.y);
 }

 Vector2 Vector2::operator-(const Vector2& other) const
 {
	 return Vector2(x - other.x, y - other.y);
 }

 Vector2 Vector2::operator*(const Vector2& other) const
 {
	 return Vector2(x * other.x, y * other.y);
 }

 Vector2 Vector2::operator/(const Vector2& other) const
 {
	 if (other.x != 0 && other.y != 0)
	 {
		 return Vector2(x / other.x, y / other.y); 
	 }
	 else
	 {
		 return Vector2::Zero;
	 }
 }

 Vector2& Vector2::operator+=(const Vector2& other) 
 {
	 x += other.x;
	 y += other.y; 
	 return *this; 
 }

 Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistDelta)
 {
	 Vector2 toTarget = target - current;

	 float distance = toTarget.GetMagnitude();

	 if (distance <= maxDistDelta || distance == 0.0f)
	 {
		 return target;
	 }
	 else
	 {
		 Vector2 direction = toTarget / distance;
		 return current + direction * maxDistDelta; 
	 }
 }

 Vector2 Vector2::operator/(float scalar) const
 {
	 if (scalar != 0)
	 {
		 return Vector2(x / scalar, y / scalar);
	 }
	 else
	 {
		 return Vector2::Zero;
	 }
 }
 Vector2 Vector2::operator*(float scalar) const
 {
	 if (scalar != 0)
	 {
		 return Vector2(x * scalar, y * scalar);
	 }
	 else
	 {
		 return Vector2::Zero; 
	 }
 }
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
