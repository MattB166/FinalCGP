#pragma once
class Vector2
{
	
public:
	float x, y;
	//float Magnitude; 
	Vector2();
	Vector2(float x, float y);
	float GetX() const;
	float GetY() const;
	void SetPosition(float x, float y);
	Vector2 Normalize(); 
	float GetMagnitude();


	
};

