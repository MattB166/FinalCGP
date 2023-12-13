#include "Tank.h"
#include "SDL.h"
#include <iostream>



Tank::Tank()
{
	
}

Tank::Tank(SDL_Texture* baseTexture, SDL_Texture* barrelTexture)
{
	m_texture = baseTexture; 
	m_barrelTexture = barrelTexture;
	std::cout <<  "Tank Created" << std::endl;
	m_w= 40;
	m_h = 35;
	Pos.x = 50;
	Pos.y= 50;
	//boxCollider.x = m_x;
	//boxCollider.y = m_y;
	SetPlayerPosition(200, 200);
	boxCollider.m_height = 35;
	boxCollider.m_width = 40;
	/////need to set min and max x and y values for collision function 
	
	
}



float Tank::MoveUp(float deltaTime)
{
	Pos.y -= m_speed * deltaTime;
	//TankPos.y -= m_speed * deltaTime;
	boxCollider.y = Pos.y;
	return Pos.y;
}

float Tank::MoveDown(float deltaTime)
{
	Pos.y += m_speed * deltaTime;
	boxCollider.y = Pos.y;
	return Pos.y;
}

float Tank::MoveLeft(float deltaTime)
{
	Pos.x -= m_speed * deltaTime;
	boxCollider.x = Pos.x;
	return Pos.x;
}


float Tank::MoveRight(float deltaTime)
{
	Pos.x += m_speed * deltaTime;
	boxCollider.x = Pos.x;
	return Pos.x; 
}

float Tank::GetXValue() const
{
	return Pos.x;
}

float Tank::GetYValue() const
{
	return Pos.y;
}

void Tank::Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer)
{
	GameObject::Draw(renderer, CameraX, CameraY, MouseX, MouseY, false);
	Vector2 PlayerPos;
	if (isPlayer)
	{
		Vector2 tankCentre = Pos + Vector2(m_w / 2, m_h / 2);
		Vector2 mouseVec = Vector2(MouseX, MouseY) - tankCentre;
		BarrelAngle = atan2(mouseVec.y, mouseVec.x) * (180.0 / M_PI) - 90; 
		PlayerPos = tankCentre;
	}
	/*else
	{
		//// need a way for the enemy barrel to be locked on to player pos 
		
	}*/
	int x = Pos.x + m_w / 2 - 8 / 2; /// setting barrel width 
	int y = Pos.y + m_h / 2;  ///setting barrel height 
	SDL_Rect dstRect{ x - CameraX ,y - CameraY ,m_w / 5,m_h / 1.3 }; //sets barrel dest to correct position
	SDL_Point BarrelAnchor = { 4,0 }; 
	
	//SDL_RenderCopy(renderer, m_barrelTexture, NULL, &dstRect);
	SDL_RenderCopyEx(renderer, m_barrelTexture, NULL, &dstRect, BarrelAngle, &BarrelAnchor, { SDL_FLIP_NONE });     
	//SDL_RenderCopyEx(renderer,m_barrelTexture,NULL,&dstRect,angle,) //last couple of parameters needed 

}




void Tank::changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture)  ////changes texture on command between 2, useful for landmines flashing 
{
	if (m_texture != newTexture)
	{
		m_texture = newTexture;
		//GameObject::Draw(renderer);
	}
	else
	{
		m_texture = baseTexture;
		//GameObject::Draw(renderer);
	}

	
}

void Tank::SetPlayerPosition(int x , int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Tank::SetEnemyPosition(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Tank::SetColliderPos(int x, int y)
{
	boxCollider.x = x;
	boxCollider.y = y; 
}

void Tank::RotateTank(float RotationAngle)
{
	rb.angle += RotationAngle;
}

void Tank::UpdateTank(float deltaTime)
{

}

void Tank::Fire()
{
	
}






