#include "Bullet.h"
#include <cmath>

Bullet::Bullet()
{

}

Bullet::Bullet(SDL_Texture* texture)
{
	m_texture = texture; 
	m_w = 5;
	m_h = 10;
	boxCollider.m_height = 10;
	boxCollider.m_width = 5; 
	//rotation = -180.0f;
	//Pos.x = 40;  //temporary values 
	//Pos.y = 40;
}


void Bullet::Fire(float TurretAngle, float TurretX, float TurretY)
{
	//from x and y of origin, through magnitude of one in vector facing forward from turret 

	
	float velocityX = bullet_Speed * cos(TurretAngle * M_PI / 180.0);
	float velocityY = bullet_Speed * sin(TurretAngle * M_PI / 180.0); 

	float offsetMagnitude = 10.0f;
	float offsetAngle = TurretAngle * (M_PI / 180.0);
	float offsetX = offsetMagnitude * cos(offsetAngle);
	float offsetY = offsetMagnitude * sin(offsetAngle);

	

	Pos.x = TurretX + offsetX;
	Pos.y = TurretY + offsetY;

	rb.velocity.x = velocityX;
	rb.velocity.y = velocityY; 

	//rotation = atan2(rb.velocity.y, rb.velocity.x) * (180.0 / M_PI);
	
	std::cout << "X Velocity is: " << bullet_Speed * cos(TurretAngle * M_PI / 180.0) << "  at angle: " << TurretAngle << std::endl; 
	std::cout << "Y Velocity is: " << bullet_Speed * sin(TurretAngle * M_PI / 180.0) << " at angle: " << TurretAngle << std::endl; 
}

void Bullet::Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	Pos.x += rb.velocity.x * deltaTime; 
	Pos.y += rb.velocity.y * deltaTime;
	
	GameObject::Draw(renderer, CameraX, CameraY, MouseX, MouseY, true, deltaTime);
	rotation = atan2(rb.velocity.y, rb.velocity.x) * (180.0 / M_PI) - 270; 
	
	
	
	//// bullets spawn and fire but not aligned with barrel rotation 
}

void Bullet::Destroy()
{
	///destroy bullet 
}


