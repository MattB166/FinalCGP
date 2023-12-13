#include "Bullet.h"
#include <cmath>

Bullet::Bullet()
{

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

void Bullet::Destroy()
{
	///destroy bullet 
}


