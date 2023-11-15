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
	m_w = 40;
	m_h = 35;
	m_x = 50;
	m_y = 50;
	//boxCollider.x = m_x;
	//boxCollider.y = m_y;
	SetPlayerPosition(200, 200);
	boxCollider.m_height = 35;
	boxCollider.m_width = 40;
	/////need to set min and max x and y values for collision function 
	
	
}



float Tank::MoveUp(float deltaTime)
{
	m_y -= m_speed * deltaTime;
	boxCollider.y = m_y;
	return m_y;
}

float Tank::MoveDown(float deltaTime)
{
	m_y += m_speed * deltaTime;
	boxCollider.y = m_y;
	return m_y;
}

float Tank::MoveLeft(float deltaTime)
{
	m_x -= m_speed * deltaTime;
	boxCollider.x = m_x;
	return m_x;
}


float Tank::MoveRight(float deltaTime)
{
	m_x += m_speed * deltaTime;
	boxCollider.x = m_x;
	return m_x; 
}

float Tank::GetXValue() const
{
	return m_x;
}

float Tank::GetYValue() const
{
	return m_y;
}

void Tank::Draw(SDL_Renderer* renderer, float CameraX, float CameraY)
{
	GameObject::Draw(renderer, CameraX, CameraY);
	int x = m_x + m_w / 2 - 8 / 2; /// setting barrel width 
	int y = m_y + m_h / 2;  ///setting barrel height 
	SDL_Rect dstRect{ x - CameraX ,y - CameraY ,m_w / 5,m_h / 1.3 }; //sets barrel dest to correct position
	SDL_RenderCopy(renderer, m_barrelTexture, NULL, &dstRect); /// renders to renderer 


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
	m_x = x;
	m_y = y;
}

void Tank::SetEnemyPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Tank::SetColliderPos(int x, int y)
{
	boxCollider.x = x;
	boxCollider.y = y; 
}






