#pragma once
class Vector2
{
	
public:
	float x, y;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2 operator/(const Vector2& other) const;

	Vector2 operator/(float scalar) const;
	Vector2 operator*(float scalar) const; 
	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Zero;
	static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistDelta);
	//float Magnitude; 
	Vector2();
	Vector2(float x, float y);
	
	float GetX() const;
	float GetY() const;
	void SetPosition(float x, float y);
	Vector2 Normalize(); 
	float GetMagnitude();


	
};

