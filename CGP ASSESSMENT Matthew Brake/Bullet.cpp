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
	Pos.x = 40;  //temporary values 
	Pos.y = 40;
}


void Bullet::Fire(float TurretAngle, float TurretX, float TurretY)
{
	//from x and y of origin, through magnitude of one in vector facing forward from turret 

	float velocityX = bullet_Speed * cos(TurretAngle * M_PI / 180.0);
	float velocityY = bullet_Speed * sin(TurretAngle * M_PI / 180.0); 

	Pos.x = TurretX;
	Pos.y = TurretY;

	rb.velocity.x = velocityX;
	rb.velocity.y = velocityY; 

	std::cout << "X Velocity is: " << bullet_Speed * cos(TurretAngle * M_PI / 180.0) << " << angle. " << std::endl; 
}

void Bullet::Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	Pos.x += rb.velocity.x * deltaTime; ///temporary. need to alter velocity in direction barrel is facing and include the speed 
	Pos.y += rb.velocity.y * deltaTime;
	
	GameObject::Draw(renderer, CameraX, CameraY, MouseX, MouseY, false, deltaTime);
	
	////does work for spawning, but they are static and overlapping 
}

void Bullet::Destroy()
{
	///destroy bullet 
}


